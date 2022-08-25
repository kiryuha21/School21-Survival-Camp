//
// Copyright 2022 lyradanu
//

#include <stdio.h>

#define ERR -1

#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
void squaring(int *a, int n);

int main() {
    int n, data[NMAX];
    if (input(data, &n) == ERR) {
        printf("n/a");
        return 0;
    }
    squaring(data, n);
    output(data, n);

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
    printf("%d", *(a + n - 1));
}

void squaring(int *a, int n) {
    for (int* i = a; i - a < n; ++i) {
        *i *= *i;
    }
}


