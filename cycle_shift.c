//
// Copyright 2022 lyradanu
//

#include <stdio.h>

#define ERR -1

#define NMAX 10

int input(int* a, int* n, int* shift);
void output(int *buffer, int length);
void shift(const int* a, int length, int shift, int* res);
void handle_error();

int main() {
    int arr[NMAX];
    int n, sh;
    if (input(arr, &n, &sh) == ERR) {
        handle_error();
    } else {
        int res[NMAX];
        shift(arr, n, sh % n, res);
        output(res, n);
    }
    return 0;
}

void handle_error() {
    printf("n/a");
}

int input(int* a, int* n, int* shift) {
    int return_code = 0;

    char sym = 0;
    int count = scanf("%d%c", n, &sym);
    if (!(count == 2 && sym == '\n' && *n > 0 && *n <= NMAX)) {
        return_code = ERR;
    }

    if (return_code != ERR) {
        int input_end = 0;
        for (int *p = a; p - a < *n - 1 && !input_end; p++) {
            sym = 0;
            if (scanf("%d%c", p, &sym) != 2 || sym != ' ') {
                return_code = ERR;
                input_end = 1;
            }
        }

        if (return_code != ERR) {
            sym = 0;
            count = scanf("%d%c", a + *n - 1, &sym);
            if (!(count == 2 && sym == '\n')) {
                return_code = ERR;
            }

            if (return_code != ERR) {
                sym = 0;
                count = scanf("%d%c", shift, &sym);
                if (!((count == 1 && sym == 0) || (count == 2 && sym == '\n'))) {
                    return_code = ERR;
                }
            }
        }
    }
    return return_code;
}

void output(int *buffer, int length) {
    for (int i = 0; i < length - 1; ++i) {
        printf("%d ", buffer[i]);
    }
    printf("%d", buffer[length - 1]);
}

void shift(const int* a, int length, int shift, int* res) {
    for (int i = 0; i < length; ++i) {
        int ind;
        if (shift > 0) {
            ind = i - shift < 0 ? i + length - shift : i - shift;
        } else {
            ind = i - shift >= length ? i - shift - length : i - shift;
        }
        res[ind] = a[i];
    }
}
