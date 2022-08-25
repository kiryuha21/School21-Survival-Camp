//
// Copyright 2022 lyradanu
//

#include <stdio.h>

#define ERR -1

#define ARR_SIZE 10

int input(int* a);
void bubble_sort(int* a);
void swap(int* first, int* second);
void output(int *a);
void handle_error();

int main() {
    int arr[ARR_SIZE];
    if (input(arr) == ERR) {
        handle_error();
    } else {
        bubble_sort(arr);
        output(arr);
    }
    return 0;
}

void handle_error() {
    printf("n/a");
}

int input(int* a) {
    int return_code = 0;
    int input_end = 0;

    for (int* p = a; p - a < ARR_SIZE - 1 && !input_end; p++) {
        char ch = 0;
        if (scanf("%d%c", p, &ch) != 2 || ch != ' ') {
            input_end = 1;
            return_code = ERR;
        }
    }

    if (return_code != ERR) {
        char sym = 0;
        int count = scanf("%d%c", (a + ARR_SIZE - 1), &sym);
        if (!((count == 1 && sym == 0) || (count == 2 && sym == '\n'))) {
            return_code = ERR;
        }
    }
    return return_code;
}

void swap(int* first, int* second) {
    int temp = *first;
    *first = *second;
    *second = temp;
}

void bubble_sort(int* a) {
    for (int* i = a; i - a < ARR_SIZE - 1; ++i) {
        for (int* j = a; j - a < ARR_SIZE - (i - a) - 1; ++j) {
            if (*j > *(j + 1)) {
                swap(j, (j + 1));
            }
        }
    }
}

void output(int *a) {
    for (int* i = a; i - a < ARR_SIZE - 1; ++i) {
        printf("%d ", *i);
    }
    printf("%d", *(a + ARR_SIZE - 1));
}




