// A program demonstrating the use of constants in C

// let's say we have a a constant like pi or Inches per pound
// instead of having magic numbers in the code, we define them as constants
#define PI 3.14159
#define INCHES_PER_POUND 166
#define RECIPROCAL_OF_PI (1.0 / PI) // if constant contains operators, use parentheses
#include <stdio.h>

// Usually constants are defined at the top of the file or in a separate header file in all caps
// This is good practice to improve code readability and maintainability
// Instead of having to scour code for magic numbers, we can just refer to the constant names, making it clear what they represent

int main() 
{
    double radius = 5.0; // could also be user input
    double circumference = 2 * PI * radius; // Using the constant PI
    double weightInPounds = 10.0;
    double weightInInches = weightInPounds * INCHES_PER_POUND; // Using the constant INCHES_PER_POUND

    printf("Circumference of circle with radius %.2f: %.2f\n", radius, circumference);
    printf("Weight in inches for %.2f pounds: %.2f\n", weightInPounds, weightInInches);
    printf("Reciprocal of PI: %.5f\n", RECIPROCAL_OF_PI);  // Preprocessor will replace this with 1.0 / 3.14159

    return 0;
}

