//
// Copyright 2022 lyradanu
//

#include <stdio.h>

#define ERR -1

#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
int max(int *a, int n);
int min(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);

void output_result(int max_v,
                   int min_v,
                   double mean_v,
                   double variance_v);

int main() {
    int n, data[NMAX];
    if (input(data, &n) == ERR) {
        printf("n/a");
        return 0;
    }
    output(data, n);
    output_result(max(data, n),
                  min(data, n),
                  mean(data, n),
                  variance(data, n));

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

void output(int *a, int n) {
    for (int* i = a; i - a < n - 1; ++i) {
        printf("%d ", *i);
    }
    printf("%d\n", *(a + n - 1));
}

void output_result(int max_v, int min_v, double mean_v, double variance_v) {
    printf("%d %d %.6lf %.6lf", max_v, min_v, mean_v, variance_v);
}

int max(int *a, int n) {
    int max = *a;
    for (int* i = a + 1; i - a < n; ++i) {
        if (*i > max) {
            max = *i;
        }
    }
    return max;
}

int min(int *a, int n) {
    int min = *a;
    for (int* i = a + 1; i - a < n; ++i) {
        if (*i < min) {
            min = *i;
        }
    }
    return min;
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


