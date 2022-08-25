#include <stdio.h>

#define ERR 1

int main() {
    double x, y;
    if (scanf("%lf%lf", &x, &y) != 2 || getchar() != '\n') {
        puts("n/a");
        return ERR;
    }

    if (x * x + y * y < 25) {
        puts("GOTCHA");
    } else {
        puts("MISS");
    }
    return 0;
}