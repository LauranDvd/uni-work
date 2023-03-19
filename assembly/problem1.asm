; statement: given a string of doublewords, compute the sum
; of the words formed by each doubleword's 1st and 3rd byte
; e.g. 1234A678h ---> 12A6h will be added to the sum
bits 32

global start

extern exit, printf
import exit msvcrt.dll  ; C functions
import printf msvcrt.dll

segment data use32 class=data
    sir dd 1234A678h, 12785634h, 1A4D3C2Bh
    len equ ($-sir)/4  ; length of sir, as no. of elements (4=sizeof(dword))
    sir2 resw len  ; the required word string
    countOnes dd 0  ; will be used to count the 1s
    formatIntUns db "%u", 0  ; asciiz: end string of characters with 0
    
segment code use32 class=code
start:
    ; First, get the word string (in sir2)
    ; Algorithm: take each dword from sir, extract one byte, put it in sir2,
    ; extract the other byte, put it in sir2.
    
    cld  ; we go from left to right. in case DF was set somewhere (to be sure)
    mov esi, sir  
    mov edi, sir2
    mov ecx, len  ; no. of times to execute loop below
    jecxz endFor  ; in case len=0
    for:
        ; first, take the byte of the lower word and store it in [edi]
        ; that is because of the little endian representation: we need the
        ; byte which is last in the word, to appear first in the memory
        ; e.g.: n=12a6 (base 16) --> in memory: A6h|12h
        
        ; extract byte
        mov al, [esi + 1]  ; skip last byte (little endian --> at [esi] we have last byte etc.)
        stosb  ; although sir2 is "declared" as a word string, it has no dtype associated and we can
        ; store one byte as a time
        
        ; extract the other byte
        mov al, [esi + 3]  ; 1st byte of the no. is actually the last in the memory layout
        stosb
        
        add esi, 4  ; go to next dword
        ; edi has already been increased above
    loop for 
    endFor:
    
    ; compute no. of bits of 1 in sir2
    ; Algorithm: iterate through the word string, and for each word, take each of the 16 bits separately
    mov esi, sir2 
    mov ecx, len 
    jecxz endFor2
    for2:
        lodsw  ; ax=next word from sir2; add esi, 2;
        
        push ecx  ; we'll have to use it in the loop below, so we save it and restore it after the nested loop is done
        mov ecx, 16  ; word=16bits. we will take each bit separately
        loopNo:
            test ax, 1  ; ax AND 1, without changing ax. just changes flags
            jz noOne
                ; enter here if ax ends in 1 (ax AND 1 != 0 implies ax AND 1 = 1, because these 2 are the only possible results)
                inc dword [countOnes]  ; inc the count
            noOne:
            shr ax, 1  ; go to next bit
        loop loopNo
        pop ecx  ; restore our loop count
    loop for2
    endFor2:
    
    ; Print countOnes
    ; syntax: printf("%u", countOnes)
    ; we use %u because countOnes is unsigned. %d could work too,
    ; as countOnes is small, so its first bit is 0, hence it's
    ; the same in both interpretations
    push dword [countOnes]
    push dword formatIntUns
    call [printf]
    add esp, 4 * 2  ; cdecl: caller frees the stack of the parameters
    
    push dword 0  
    call [exit]  ; exit the program peacefully
    