#include <stdio.h>

// Function that takes 3 integers by reference and returns their sum
int add(int *a, int *b, int *c) {
    return (*a + *b + *c);
}

int main() {
    int num1, num2, num3;

    // Input the integers
    printf("Enter three integers: ");
    scanf("%d %d %d", &num1, &num2, &num3);

    // Call the add function and pass the integers by reference
    int result = add(&num1, &num2, &num3);

    // Output the result
    printf("The sum of %d, %d, and %d is: %d\n", num1, num2, num3, result);

    return 0;
}

