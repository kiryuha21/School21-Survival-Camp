//
// Copyright 2022 lyradanu
//

#include <stdio.h>
#include <stdlib.h>

#define ERR -1

void swap(int* first, int* second);
int* input(int *a, int* n, int* err);
void bubble_sort(int* a, int n);
void output(int *a, int n);
void handle_error();

int main() {
    int* arr = NULL;
    int size;
    int err = 0;

    arr = input(arr, &size, &err);
    if (err != 0) {
        handle_error();
    } else {
        bubble_sort(arr, size);
        output(arr, size);
    }
    free(arr);
    return 0;
}

void handle_error() {
    printf("n/a");
}

int* input(int *a, int* n, int* err) {
    char sym = 0;
    if (scanf("%d%c", n, &sym) != 2 || sym != '\n' || *n <= 0) {
        *err = ERR;
    }

    if (*err != ERR) {
        a = (int*)calloc(*n, sizeof(int));
        if (a == NULL) {
            *err = ERR;
        }

        if (*err != ERR) {
            int input_end = 0;
            for (int *p = a; p - a < *n - 1 && !input_end; p++) {
                if (scanf("%d%c", p, &sym) != 2 || sym != ' ') {
                    input_end = 1;
                    *err = ERR;
                    free(a);
                    a = NULL;
                }
            }

            if (*err != ERR) {
                sym = 0;
                int count = scanf("%d%c", (a + *n - 1), &sym);
                if (!((count == 1 && sym == 0) || (count == 2 && sym == '\n'))) {
                    *err = ERR;
                    free(a);
                    a = NULL;
                }
            }
        }
    }
    return a;
}

void swap(int* first, int* second) {
    int temp = *first;
    *first = *second;
    *second = temp;
}

void bubble_sort(int* a, int n) {
    for (int* i = a; i - a < n - 1; ++i) {
        for (int* j = a; j - a < n - (i - a) - 1; ++j) {
            if (*j > *(j + 1)) {
                swap(j, (j + 1));
            }
        }
    }
}

void output(int *a, int n) {
    for (int* i = a; i - a < n - 1; ++i) {
        printf("%d ", *i);
    }
    printf("%d", *(a + n - 1));
}




