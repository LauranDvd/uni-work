// statement: two character arrays are given
// in another array, put the digits from a, then the digits from b
// in another array, do it in the opposite order
#include <stdio.h>

char a[101] = "12trtr asc number 34k5 67 8f9";
char b[101] = "tr98tr van7 6a nu5mbe4  r32 f1";
char result[101] = "";
char resultVv[101] = "";

void takeDigits(char* dest, char* src);  // in the asm module

int main()
{
    takeDigits(result, a);
    char* p = result;
    while (*p)
        p++;
    takeDigits(p, b);
    
    printf("First string, then second string: %s \n", result);
    
    takeDigits(resultVv, b);
    p = resultVv;
    while (*p)
        p++;
    takeDigits(p, a);
    
    printf("Second string, then first string: %s", resultVv);
    
    return 0;
}
