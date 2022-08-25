#include <stdio.h>

#define ERR -1

int abs(int num) {
    if (num < 0) {
        return -num;
    }
    return num;
}

int division(int a, int b, int* res, int* mod) {
    if (b == 0) {
        return ERR;
    }

    int abs_a = abs(a);
    int abs_b = abs(b);

    *res = 0;
    while (abs_a >= abs_b) {
        *res += 1;
        abs_a -= abs_b;
    }

    if ((a > 0 && b < 0) || (a < 0 && b > 0)) {
        *res = -*res;
    }
    *mod = a - *res * b;
    return 0;
}

int maxPrimeDivider(int n) {
    int div_res, mod;
    int result = 1;

    n = abs(n);

    int d = 2;
    while (d * d <= n) {
        division(n, d, &div_res, &mod);
        if (mod == 0) {
            result = d;
            n /= d;
        } else {
            d += 1;
        }
    }
    if (n > 1) {
        result = n;
    }
    return result;
}

int main() {
    int num;
    if (scanf("%d", &num) != 1 || num == 0 || getchar() != '\n') {
        printf("n/a");
        return 0;
    }

    printf("%d", maxPrimeDivider(num));
    return 0;
}
