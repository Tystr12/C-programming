#include <stdio.h>

#define TAX_RATE 0.05f // 5% tax rate

int main(void)
{
    float amount, total;

    printf("Enter the amount: ");
    scanf("%f", &amount);
    total = amount + (amount * TAX_RATE);
    printf("Amount before tax: $%.2f", amount);
    printf("\n                  ---------------");
    printf("\nTotal amount with tax: $%.2f\n", total);

    return 0;
}