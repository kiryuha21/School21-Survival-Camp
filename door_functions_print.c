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

void print_function(double(*func)(double), double min, double max, double cell) {
    for (double i = -M_PI; i <= M_PI; i += STEP) {
        double an = func(i);
        if (isnan(an)) {
            puts("");
            continue;
        }

        double min_diff = double_abs(min - an);
        double res = min;

        for (double j = min + cell; j <= max; j += cell) {
            double diff = double_abs(j - an);
            if (diff < min_diff) {
                min_diff = diff;
                res = j;
            }
        }

        for (double j = min; j <= max; j += cell) {
            if (double_abs(res - j) <= EPS) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        puts("");
    }
}

int main() {
    double anezi_max, anezi_min = anezi(-M_PI);
    double bernulli_max, bernulli_min;
    double hyperbola_max, hyperbola_min = hyperbola(-M_PI);

    for (double i = -M_PI; i <= M_PI; i += STEP) {
        double an = anezi(i);
        if (an > anezi_max) {
            anezi_max = an;
        }
        if (an < anezi_min) {
            anezi_min = an;
        }

        double hyp = hyperbola(i);
        if (hyp > hyperbola_max) {
            hyperbola_max = hyp;
        }
        if (hyp < hyperbola_min) {
            hyperbola_min = hyp;
        }

        if (sqrt(1 + 4 * i * i) - i * i - 1 >= 0) {
            double ber = bernulli(i);
            if (ber > bernulli_max) {
                bernulli_max = ber;
            }
            if (ber < bernulli_min) {
                bernulli_min = ber;
            }
        }
    }

    double anezi_cell = (anezi_max - anezi_min) / 20;

    double bernulli_cell = (bernulli_max - bernulli_min) / 20;

    double hyperbola_cell = (hyperbola_max - hyperbola_min) / 20;

    print_function(anezi, anezi_min, anezi_max, anezi_cell);
    print_function(bernulli, bernulli_min, bernulli_max, bernulli_cell);
    print_function(hyperbola, hyperbola_min, hyperbola_max, hyperbola_cell);

    return 0;
}

