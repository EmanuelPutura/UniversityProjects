/*++
  Write a C/C++ program which calls the <strong>asmConcat</strong> function written in assembly language. 
  This function has as parameter a character string read in the C/C++ program, reads another character string using the <strong>readString</strong> C/C++ function, and accesses an additional character string which is a global variable of the C/C++ program (called <strong> stringC </strong>). 
  The function <strong>asmConcat</strong> builds and returns as a result the string obtained by concatenating the first 10 characters of each of the 3 strings. 
  This string will be printed on the screen. 
 --*/


#include <stdio.h>

// the function declared in modulConcatenate.asm
int asmConcat(char sir[], char sirR[]);

// the function used for reading a string from keyboard
void readString(char sir[]);

// global string accessed from asmConcat
char str3[] = "0011223344";

int main()
{
    char str1[11];
    char strRez[31] = "";
    int lenStrRez = 0;

    printf("! we assume that the strings read from keyboard contain 10 characters!! (we do not validate)\n");
    printf("String 1 read from the C module: ");
    readString(str1);

    lenStrRez = asmConcat(str1, strRez);
    printf("\nResult string of length %d:\n%s", lenStrRez, strRez);
    return 0;
}

void readString(char sir[])
{
    scanf("%s", sir);
}