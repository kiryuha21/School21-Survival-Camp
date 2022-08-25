#include <stdio.h>
#include <math.h>

#define STEP M_PI * 2 / 41
#define EPS 1e-6

double double_abs(double num) {
    if (num < 0) {
        return -num;
    }
    return num;
}

double anezi(double x) {
    return 1 / (1 + x * x);
}

double bernulli(double x) {
    return sqrt(sqrt(1 + 4 * x * x) - x * x - 1);
}

double hyperbola(double x) {
    return 1 / (x * x);
}

int main() {
    for (double i = -M_PI; i <= M_PI; i += STEP) {
        double an = anezi(i);
        double hyp = hyperbola(i);

        printf("%.7lf | %.7lf ", i, an);
        if (sqrt(1 + 4 * i * i) - i * i - 1 < 0) {
            printf("| - | ");
        } else {
            double ber = bernulli(i);
            printf("| %.7lf | ", ber);
        }
        printf("%.7lf\n", hyp);
    }

    return 0;
}
