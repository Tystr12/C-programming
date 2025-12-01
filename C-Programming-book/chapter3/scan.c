// Test program to study how scanf works. 
// experiment with different inputs and see what is printed out
#include <stdio.h>

int main() {
    // Write C code here
    int i, j;
    float x, y;
    
    scanf("%d%d%f%f", &i, &j, &x, &y);
    
    printf("The values are \n");
    printf("i: %d \n", i);
    printf("j: %d \n", j);
    printf("x: %.2f \n",x);
    printf("y: %.2f \n", y);

    

    return 0;
}
