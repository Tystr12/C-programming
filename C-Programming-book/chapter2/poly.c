#include <stdio.h>

float func(float x) 
{
    float result;
    result = (3*x*x*x*x*x) + (2*x*x*x*x) - (5*x*x*x) - (x*x) + (7*x) - 6;
    return result;
}

int main(void)
{
    float x;
    printf("Enter a value for x: ");
    scanf("%f", &x);
    float result = func(x);
    printf("The result of the polynomial is: %.2f\n", result);
    return 0;
}