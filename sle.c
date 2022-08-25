#include <stdlib.h>
#include <stdio.h>

#define ERR -1

double* sle(double **matrix, int n, int* err);
double** input(double **matrix, int *n, int *m, int* err);
void output_roots(double *roots, int n);
void handle_error();
double** init_empty(int rows, int cols, int* err);
double** input_base(double** arr, int rows, int cols, int* err);
double** clear_and_stop(double** arr, int* err, int* input_end, int row);
int input_size(int* rows, int* cols);
double** clear_matrix(double** arr, int rows);

int main() {
    double** matrix = NULL;
    int err = 0;
    int rows, cols;
    matrix = input(matrix, &rows, &cols, &err);
    if (err != ERR) {
        double* result = sle(matrix, rows, &err);
        if (err == ERR) {
            handle_error();
        } else {
            output_roots(result, rows);
        }
        if (result != NULL) {
            free(result);
        }
    } else {
        handle_error();
    }
    clear_matrix(matrix, rows - 1);
    return 0;
}

void output_roots(double *roots, int n) {
    for (int i = 0; i < n - 1; ++i) {
        printf("%.6lf ", roots[i]);
    }
    printf("%.6lf", roots[n - 1]);
}

double* sle(double** matrix, int n, int* err) {
    double* result = NULL;
    double** clone = init_empty(n, n + 1, err);
    if (*err != ERR) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n + 1; j++) {
                clone[i][j] = matrix[i][j];
            }
        }

        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n + 1; i++) {
                clone[k][i] = clone[k][i] / matrix[k][k];
            }
            for (int i = k + 1; i < n; i++) {
                double K = clone[i][k] / clone[k][k];
                for (int j = 0; j < n + 1; j++) {
                    clone[i][j] = clone[i][j] - clone[k][j] * K;
                }
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n + 1; j++) {
                    matrix[i][j] = clone[i][j];
                }
            }
        }

        for (int k = n - 1; k > -1; k--) {
            for (int i = n; i > -1; i--) {
                clone[k][i] = clone[k][i] / matrix[k][k];
            }
            for (int i = k - 1; i > -1; i--) {
                double K = clone[i][k] / clone[k][k];
                for (int j = n; j > -1; j--) {
                    clone[i][j] = clone[i][j] - clone[k][j] * K;
                }
            }
        }

        result = (double*)(calloc(n, sizeof(double)));
        if (result == NULL) {
            result = NULL;
            *err = ERR;
        } else {
            for (int i = 0; i < n; i++) {
                result[i] = clone[i][n];
            }
        }
    }
    clear_matrix(clone, n - 1);

    return result;
}

void handle_error() {
    printf("n/a");
}

double** init_empty(int rows, int cols, int* err) {
    double** arr = (double**)(calloc(rows, sizeof(double*)));
    if (arr == NULL) {
        *err = ERR;
    } else {
        int input_end = 0;
        for (int i = 0; i < rows && !input_end; ++i) {
            arr[i] = (double*)(calloc(cols, sizeof(double)));
            if (arr[i] == NULL) {
                arr = clear_and_stop(arr, err, &input_end, i);
            }
        }
    }
    return arr;
}

double** input_base(double** arr, int rows, int cols, int* err) {
    arr = init_empty(rows, cols, err);
    if (*err == 0) {
        int input_end = 0;
        for (int i = 0; i < rows && !input_end; ++i) {
            for (int j = 0; j < cols - 1 && !input_end; ++j) {
                char sym = 0;
                if (scanf("%lf%c", &arr[i][j], &sym) != 2 || sym != ' ') {
                    arr = clear_and_stop(arr, err, &input_end, rows - 1);
                }
            }
            if (*err == 0) {
                char sym = 0;
                int count = scanf("%lf%c", &arr[i][cols - 1], &sym);
                if (!((count == 2 && sym == '\n') || (count == 1 && sym == 0))) {
                    arr = clear_and_stop(arr, err, &input_end, rows - 1);
                }
            }
        }
    }
    return arr;
}

double** input(double **matrix, int *n, int *m, int* err) {
    *err = input_size(n, m);
    if (*err == 0) {
        matrix = input_base(matrix, *n, *m, err);
    }
    return matrix;
}

double** clear_and_stop(double** arr, int* err, int* input_end, int row) {
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

double** clear_matrix(double** arr, int rows) {
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

