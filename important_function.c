#include <math.h>
#include <stdio.h>

#define EPS 1e-6

#define ERR 1

double calculate(double x) {
    double first = 7e-3 * pow(x, 4);
    double second = ((22.8 * pow(x, 1 / 3) - 1e3) * x + 3) / (pow(x, 2) / 2);
    double third = x * pow(10 + x, 2 / x);
    return first + second - third - 1.01;
}

int main() {
    double num;
    if (scanf("%lf", &num) != 1 || getchar() != '\n') {
        puts("n/a");
        return ERR;
    }

    if (num > -EPS && num < EPS) {
        puts("n/a");
        return ERR;
    }

    printf("%.1lf\n", calculate(num));
    return 0;
}
