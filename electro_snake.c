#include <stdlib.h>
#include <stdio.h>

#define ERR -1

/*
    1 6 7
    2 5 8
    3 4 9
*/
void sort_vertical(const int* sorted, int n, int m, int **result_matrix);

/*
    1 2 3
    6 5 4
    7 8 9
*/
void sort_horizontal(const int* sorted, int n, int m, int **result_matrix);

void swap(int* first, int* second);
int** input(int **matrix, int *n, int *m, int* err);
void output(int **matrix, int n, int m);
int** init_empty(int rows, int cols, int* err);
int** clear_matrix(int** arr, int rows);
int** clear_and_stop(int** arr, int* err, int* input_end, int row);
int** input_base(int** arr, int rows, int cols, int* err);
int input_size(int* rows, int* cols);
int* fill_sorted(int** matrix, int* arr, int rows, int cols, int* err);
void handle_error();
void print_line();


int main() {
    int **matrix = NULL, **result = NULL;
    int* sorted_arr = NULL;
    int n, m;
    int err;

    matrix = input(matrix, &n, &m, &err);
    if (err != ERR) {
        result = init_empty(n, m, &err);
        if (err != ERR) {
            sorted_arr = fill_sorted(matrix, sorted_arr, n, m, &err);
            if (err != ERR) {
                sort_vertical(sorted_arr, n, m, result);
                output(result, n, m);

                print_line();
                print_line();

                sort_horizontal(sorted_arr, n, m, result);
                output(result, n, m);
            } else {
                handle_error();
            }
        } else {
            handle_error();
        }
    } else {
        handle_error();
    }
    clear_matrix(matrix, n - 1);
    clear_matrix(result, n - 1);
    if (sorted_arr != NULL) {
        free(sorted_arr);
    }
    return 0;
}

void print_line() {
    puts("");
}

int* fill_sorted(int** matrix, int* arr, int rows, int cols, int* err) {
    int new_size = rows * cols;

    arr = (int*)(calloc(new_size, sizeof(int)));
    if (arr == NULL) {
        *err = ERR;
    } else {
        int count = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                arr[count] = matrix[i][j];
                ++count;
            }
        }
    }

    for (int i = 0; i + 1 < new_size; ++i) {
        for (int j = 0; j + 1 < new_size - i; ++j) {
            if (arr[j + 1] < arr[j]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
    return arr;
}

void swap(int* first, int* second) {
    int temp = *first;
    *first = *second;
    *second = temp;
}

void handle_error() {
    printf("n/a");
}

void sort_vertical(const int* sorted, int n, int m, int **result_matrix) {
    int row_pos = 0, col_pos = 0;
    int count = 0;
    int direction = 1;
    while (count != n * m) {
        result_matrix[row_pos][col_pos] = sorted[count];
        ++count;
        if (row_pos + direction == n) {
            ++col_pos;
            direction = -1;
        } else if (row_pos + direction == -1) {
            ++col_pos;
            direction = 1;
        } else {
            row_pos += direction;
        }
    }
}

void sort_horizontal(const int* sorted, int n, int m, int **result_matrix) {
    int row_pos = 0, col_pos = 0;
    int count = 0;
    int direction = 1;
    while (count != n * m) {
        result_matrix[row_pos][col_pos] = sorted[count];
        ++count;
        if (col_pos + direction == m) {
            ++row_pos;
            direction = -1;
        } else if (col_pos + direction == -1) {
            ++row_pos;
            direction = 1;
        } else {
            col_pos += direction;
        }
    }
}

void output(int **matrix, int n, int m) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < m - 1; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("%d\n", matrix[i][m - 1]);
    }

    for (int i = 0; i < m - 1; ++i) {
        printf("%d ", matrix[n - 1][i]);
    }
    printf("%d", matrix[n - 1][m - 1]);
}

int** init_empty(int rows, int cols, int* err) {
    int** arr = (int**)(calloc(rows, sizeof(int*)));
    if (arr == NULL) {
        *err = ERR;
    } else {
        int input_end = 0;
        for (int i = 0; i < rows && !input_end; ++i) {
            arr[i] = (int*)(calloc(cols, sizeof(int)));
            if (arr[i] == NULL) {
                arr = clear_and_stop(arr, err, &input_end, i);
            }
        }
    }
    return arr;
}

int** input_base(int** arr, int rows, int cols, int* err) {
    arr = init_empty(rows, cols, err);
    if (*err == 0) {
        int input_end = 0;
        for (int i = 0; i < rows && !input_end; ++i) {
            for (int j = 0; j < cols - 1 && !input_end; ++j) {
                char sym = 0;
                if (scanf("%d%c", &arr[i][j], &sym) != 2 || sym != ' ') {
                    arr = clear_and_stop(arr, err, &input_end, rows - 1);
                }
            }
            if (*err == 0) {
                char sym = 0;
                int count = scanf("%d%c", &arr[i][cols - 1], &sym);
                if (!((count == 2 && sym == '\n') || (count == 1 && sym == 0))) {
                    arr = clear_and_stop(arr, err, &input_end, rows - 1);
                }
            }
        }
    }
    return arr;
}

int** input(int **matrix, int *n, int *m, int* err) {
    *err = input_size(n, m);
    if (*err == 0) {
        matrix = input_base(matrix, *n, *m, err);
    }
    return matrix;
}

int** clear_and_stop(int** arr, int* err, int* input_end, int row) {
    *err = ERR;
    *input_end = 1;
    clear_matrix(arr, row);
    arr = NULL;
    return arr;
}

int input_size(int* rows, int* cols) {
    int return_code = 0;
    char sym = 0;
    int count = scanf("%d%d%c", rows, cols, &sym);
    if (!(count == 3 && sym == '\n' && *rows > 0 && *cols > 0)) {
        return_code = ERR;
    }
    return return_code;
}

int** clear_matrix(int** arr, int rows) {
    if (arr != NULL) {
        for (int j = rows; j >= 0; --j) {
            if (arr[j] != NULL) {
                free(arr[j]);
            }
        }
        free(arr);
    }
    arr = NULL;
    return arr;
}
