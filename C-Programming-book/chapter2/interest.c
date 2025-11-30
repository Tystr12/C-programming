#include <stdio.h>

int main(void) 
{
    float loanAmount;
    float annualInterestRate;
    float monthlyPayment;

    printf("Enter amount of loan: ");
    if (scanf("%f", &loanAmount) != 1) { fprintf(stderr, "Invalid input\n"); return 1; }
    printf("Enter annual interest rate (in %%): ");
    if (scanf("%f", &annualInterestRate) != 1) { fprintf(stderr, "Invalid input\n"); return 1; }
    printf("Enter monthly payment: ");
    if (scanf("%f", &monthlyPayment) != 1) { fprintf(stderr, "Invalid input\n"); return 1; }

    float balance = loanAmount;
    float monthlyRate = annualInterestRate / 12.0f / 100.0f;

    /* print balance before any payments */
    printf("\nBalance remaining after 0 payment: %.2f\n", balance);

    for (int i = 1; i <= 3; i++) 
    {
        float interest = balance * monthlyRate;
        balance = balance + interest - monthlyPayment;
        printf("Balance remaining after %d payment: %.2f\n", i, balance);
    }

    return 0;
}