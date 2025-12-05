// Write a program that asks the user to enter a two-digit number,
// Then prints the number with its digits reversed.


#include <stdio.h>


int main(void) 
{
    int number;

    printf("Enter a three-digit number: ");
    scanf(" %d, %d, %d\n", &number);

    int firstDigit = number / 100; // gets the first digit
    int secondDigit = (number /10) % 10; // gets the second digit
    int thirdDigit = number % 10; // gets the last digit

    printf("1: %d ", firstDigit);
    printf("2: %d ", secondDigit);
    printf("3: %d ", thirdDigit);


    printf("\nThe reversal is: %d%d%d", thirdDigit ,secondDigit, firstDigit);

    return 0;
}

