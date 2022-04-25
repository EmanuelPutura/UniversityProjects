#include <stdio.h>

// declaration of the function from the .asm file
int printWithFormat(const char* format, int number);

int main()
{
    const char* format_b8    = "%d (in base 10) = %o (in base 8)\n";
    const char* format_ascii = "The character with the ASCII code %d is %c\n\n";
    
    printf("Problem no. 8\n");
    for (int number = 32; number <= 126; ++number)
    {
        printWithFormat(format_b8, number);
        printWithFormat(format_ascii, number);
    }
    
    return 0;
}