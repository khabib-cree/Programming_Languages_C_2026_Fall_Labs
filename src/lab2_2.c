#include <stdio.h>

long long factorial(int n) {
    long long fact = 1;
    for (int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

int main() {
    int n;
    printf("Enter a non-negative integer n: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    if (n < 0) {
        printf("Error: Factorial is not defined for negative numbers.\n");
    } else {
        long long result = factorial(n);
        printf("Factorial of %d is %lld\n", n, result);
    }

    return 0;
}
