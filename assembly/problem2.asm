bits 32

global _takeDigits

segment data use32 public data


segment code use32 public code
_takeDigits:
    push ebp
    mov ebp, esp
    pusha
    
    ; syntax: takeDigits(destAddress, srcAddress)
    mov esi, [ebp + 12]
    mov edi, [ebp + 8]
    
    .whileLoop:
        lodsb
        cmp al, '0'
        jb .notDigit
        cmp al, '9'
        ja .notDigit
            ; it's a digit
            stosb
        .notDigit:
    cmp byte [esi], 0
    jne .whileLoop
    
    
    popa
    mov esp, ebp
    pop ebp
    ret
    