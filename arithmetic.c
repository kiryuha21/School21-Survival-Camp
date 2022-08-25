#include <stdio.h>

#define ERR 1

int sum(int a, int b) { return a + b; }

int sub(int a, int b) { return a - b; }

int mul(int a, int b) { return a * b; }

int div(int a, int b) { return a / b; }

int main() {
    int first, second;
    if (scanf("%d%d", &first, &second) != 2 || getchar() != '\n') {
        puts("n/a");
        return ERR;
    }

    printf("%d %d %d", sum(first, second), sub(first, second), mul(first, second));
    if (second == 0) {
        printf(" %s\n", "n/a");
    } else {
        printf(" %d\n", div(first, second));
    }
    return 0;
}
