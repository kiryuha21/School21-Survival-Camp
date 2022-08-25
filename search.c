//
// Copyright 2022 lyradanu
//

#include <stdio.h>
#include <math.h>

#define ERR -1

#define NMAX 30

int input(int *a, int *n);
double mean(int *a, int n);
double variance(int *a, int n);
int find(int* a, int n);

int main() {
    int n, data[NMAX];
    if (input(data, &n) == ERR) {
        printf("n/a");
        return 0;
    }

    printf("%d", find(data, n));
    return 0;
}

int input(int *a, int *n) {
    if (scanf("%d", n) != 1 || getchar() != '\n' || *n <= 0 || *n > NMAX) {
        return ERR;
    }
    for (int* p = a; p - a < *n - 1; p++) {
        if (scanf("%d", p) != 1 || getchar() != ' ') {
            return ERR;
        }
    }

    char sym = 0;
    int count = scanf("%d%c", (a + *n - 1), &sym);
    if (!((count == 1 && sym == 0) || (count == 2 && sym == '\n'))) {
        return ERR;
    }
    return 0;
}

int find(int* a, int n) {
    int res = 0;
    int mid = mean(a, n);
    int var = variance(a, n);

    for (int* i = a; i - a < n; i++) {
        if (*i % 2 == 0 &&
            *i >= mid &&
            *i <= mid + 3 * sqrt(var) &&
            *i != 0) {
            res = *i;
        }
    }

    return res;
}

double mean(int *a, int n) {
    double sum = 0;
    for (int* i = a; i - a < n; ++i) {
        sum += *i;
    }
    return sum / n;
}

double variance(int *a, int n) {
    double sum = 0;
    double mid = mean(a, n);

    for (int* i = a; i - a < n; ++i) {
        sum += (*i - mid) * (*i - mid);
    }

    return sum / n;
}



