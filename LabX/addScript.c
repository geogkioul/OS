#include <stdio.h>

// Function that takes three integers by reference and returns their sum
int add(int *a, int *b, int *c) {
    return *a + *b + *c;  // Dereference the pointers to get the values and return the sum
}

int main() {
    int num1, num2, num3;
    
    // Ask for user input
    printf("Enter three integers: ");
    scanf("%d %d %d", &num1, &num2, &num3);

    // Call add() function with integers passed by reference
    int sum = add(&num1, &num2, &num3);

    // Output the result
    printf("The sum of %d, %d, and %d is: %d\n", num1, num2, num3, sum);

    return 0;
}
