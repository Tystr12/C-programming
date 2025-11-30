#include <stdio.h>

#define BILL_20 20.0
#define BILL_10 10.0
#define BILL_5 5.0
#define BILL_1 1.0

int main (void)
{
    float dollarAmount;
    printf("Enter a value for dollarAmount: ");
    scanf("%f", &dollarAmount);
    
    float count20 = 0;
    float count10 = 0;
    float count5 = 0;
    float count1 = 0;

    while (dollarAmount >= BILL_20) {
        dollarAmount -= BILL_20;
        count20 += 1;
    }
    while (dollarAmount >= BILL_10) {
        dollarAmount -= BILL_10;
        count10 += 1;
    }
    while (dollarAmount >= BILL_5) {
        dollarAmount -= BILL_5;
        count5 += 1;
    }
    while (dollarAmount >= BILL_1) {
        dollarAmount -= BILL_1;
        count1 += 1;
    }
    
    printf("Number of $20 bills: %.0f\n", count20);
    printf("Number of $10 bills: %.0f\n", count10);
    printf("Number of $5  bills: %.0f\n", count5);
    printf("Number of $1  bills: %.0f\n", count1);

    
    return 0;
}