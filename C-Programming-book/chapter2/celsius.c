#include <stdio.h>

#define FREEXZING_POINT 32.0f
#define SCALE_FACTOR (5.0f / 9.0f)

//Since constants are preproccessor directives, we do not use a semicolon at the end of the line

int main(void) 
{
    float celsius;
    float fahrenheit;

    printf("Enter temperature in Fahrenheit: ");
    scanf("%f", &fahrenheit);

    celsius = (fahrenheit - FREEXZING_POINT) * SCALE_FACTOR; // Using defined constants

    printf("Temperature in Celsius: %.1f\n", celsius);

    return 0;
}
