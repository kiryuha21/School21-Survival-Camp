#include <stdio.h>

int fib(int n) {
    if (n > 0 && n <= 2) {
        return 1;
    }
    return fib(n - 1) + fib(n - 2);
}

int main() {
    int num;
    if (scanf("%d", &num) != 1) {
        printf("n/a");
        return 0;
    }

    if (num < 1) {
        printf("n/a");
        return 0;
    }

    printf("%d", fib(num));
    return 0;
}
