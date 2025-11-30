// We can think of A C program as a sequence of tokens
// Tokens are the smallest elements of a program that are meaningful to the compiler
#include <stdio.h>

int main(void) 
{
    int a = 5;          // 'int', 'a', '=', '5', ';' are tokens
    float b = 3.14f;   // 'float', 'b', '=', '3.14f', ';' are tokens
    char c = 'A';      // 'char', 'c', '=', ''A'', ';' are tokens
    int height = 180;  // 'int', 'height', '=', '180', ';' are tokens
    int sum = a + (int)b; // '+', '(', ')', and type cast '(int)' are also tokens

    printf(  "Height: %d\n"  , height    ); // 'printf', '(', '"Height: %d\n"', ',', 'height', ')' are tokens

    printf("Sum: %d\n", sum); // 'printf', '(', '"Sum: %d\n"', ',', 'sum', ')' are tokens

    return 0; // 'return', '0', ';' are tokens
}