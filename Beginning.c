//Name: Beginning.c
//Purpose: A simple C program that prints a famous quote to the console.
//Author: Ty Strong
//Date: 2025-11-13

#include <stdio.h>

void calculateBox() 
{
    int height = 8;
    int length = 12;
    int width = 10;
    int volume = height * length * width;
    printf("Dimensions: %dx%dx%d\n", length, width, height);
    printf("Volume: %d\n", volume);
}

void customBox() 
{
    int height, length, width, volume, weight;

    // remember to pass address of the variable to scanf
    printf("Enter height: ");
    scanf("%d", &height);
    printf("Enter length: ");
    scanf("%d", &length);
    printf("Enter width: ");
    scanf("%d", &width);

    volume = height * length * width;
    weight = (volume + 165) / 166;
    
    printf("Volume (cubic inches): %d\n", volume);
    printf("Dimensional weight (pounds): %d\n", weight);

}

int main() 
{
    float number = 42.0f;
    printf("Number: %f\n", number);
    printf("To C, or not to C, that is the question.\n");
    calculateBox();
    customBox();
    return 0;
}


