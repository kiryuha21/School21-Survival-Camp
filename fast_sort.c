//
// Copyright 2022 lyradanu
//

#include <stdio.h>

#define ERR -1

#define ARR_SIZE 10

int input(int* a);
void copy_arr(int* src, int* dest);
void quicksort(int* number, int first, int last);
void heap_sort(int* a);
void heapify(int* arr, int n, int i);
void swap(int* first, int* second);
void output(int *a);
void handle_error();
void print_line();

int main() {
    int arr[ARR_SIZE];
    if (input(arr) == ERR) {
        handle_error();
    } else {
        int arr_copy[ARR_SIZE];
        copy_arr(arr, arr_copy);

        heap_sort(arr);
        output(arr);
        print_line();
        quicksort(arr_copy, 0, ARR_SIZE - 1);
        output(arr_copy);
    }
    return 0;
}

void handle_error() {
    printf("n/a");
}

void print_line() {
    puts("");
}

int input(int* a) {
    int return_code = 0;
    int input_end = 0;

    for (int* p = a; p - a < ARR_SIZE - 1 && !input_end; p++) {
        char sym = 0;
        if (scanf("%d%c", p, &sym) != 2 || sym != ' ') {
            return_code = ERR;
            input_end = 1;
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

void copy_arr(int* src, int* dest) {
    for (int* i = src; i - src < ARR_SIZE; ++i) {
        *(dest + (i - src)) = *i;
    }
}

void swap(int* first, int* second) {
    int temp = *first;
    *first = *second;
    *second = temp;
}

void heapify(int* arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && *(arr + left) > *(arr + largest)) {
        largest = left;
    }

    if (right < n && *(arr + right) > *(arr + largest)) {
        largest = right;
    }

    // Swap and continue heapifying if root is not largest
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heap_sort(int* arr) {
    for (int i = ARR_SIZE / 2 - 1; i >= 0; i--) {
        heapify(arr, ARR_SIZE, i);
    }

    for (int* i = arr + ARR_SIZE - 1; i - arr >= 0; i--) {
        swap(arr, i);
        heapify(arr, i - arr, 0);
    }
}

void quicksort(int* arr, int first, int last) {
    if (first < last) {
        int pivot = first;
        int i = first;
        int j = last;
        while (i < j) {
            while (i < last && arr[i] <= arr[pivot]) {
                ++i;
            }
            while (arr[j] > arr[pivot]) {
                --j;
            }
            if (i < j) {
                swap(arr + i, arr + j);
            }
        }
        swap(arr + pivot, arr + j);
        quicksort(arr, first, j - 1);
        quicksort(arr, j + 1, last);
    }
}

void output(int *a) {
    for (int* i = a; i - a < ARR_SIZE - 1; ++i) {
        printf("%d ", *i);
    }
    printf("%d", *(a + ARR_SIZE - 1));
}




