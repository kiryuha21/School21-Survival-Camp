#include <stdio.h>
#include <stdlib.h>

#define ERR -1

double** invert(double** matrix, int rows, int cols, int* err);
void output(double **matrix, int n, int m);
int minus_row_col(double **origin_matrix, double **temp_matrix, int row, int col, int rows);
double recursive_det(double **origin_matrix, int rows, int cols, int* err);
double** input(double **matrix, int *n, int *m, int* err);
double** init_empty(int rows, int cols, int* err);
double** clear_matrix(double** arr, int rows);
double** clear_and_stop(double** arr, int* err, int* input_end, int row);
double** input_base(double** arr, int rows, int cols, int* err);
int input_size(int* rows, int* cols);
void handle_error();


int main() {
    double** matrix = NULL;
    int err = 0;
    int rows, cols;
    matrix = input(matrix, &rows, &cols, &err);
    if (err != ERR) {
        double** result = invert(matrix, rows, cols, &err);
        if (err == ERR) {
            handle_error();
        } else {
            output(result, rows, cols);
        }
        clear_matrix(result, rows - 1);
    } else {
        handle_error();
    }
    clear_matrix(matrix, rows - 1);
    return 0;
}

void output(double **matrix, int n, int m) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < m - 1; ++j) {
            printf("%.6lf ", matrix[i][j]);
        }
        printf("%.6lf\n", matrix[i][m - 1]);
    }

    for (int i = 0; i < m - 1; ++i) {
        printf("%.6lf ", matrix[n - 1][i]);
    }
    printf("%.6lf", matrix[n - 1][m - 1]);
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
    if (!(count == 3 && sym == '\n' && *rows > 0 && *cols > 0 && *rows == *cols)) {
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

int minus_row_col(double **origin_matrix, double **temp_matrix, int row, int col, int rows) {
    int miss_row = 0;

    for (int i = 0; i < rows - 1; ++i) {
        if (i == row) {
            miss_row = 1;
        }
        int miss_col = 0;
        for (int j = 0; j < rows - 1; ++j) {
            if (j == col) {
                miss_col = 1;
            }
            temp_matrix[i][j] = origin_matrix[i + miss_row][j + miss_col];
        }
    }
    return 0;
}

double recursive_det(double **origin_matrix, int rows, int cols, int* err) {
    double temp_det = 0;

    if (rows == 1) {
        temp_det = origin_matrix[0][0];
    } else {
        if (rows == 2) {
            temp_det = origin_matrix[0][0] * origin_matrix[1][1] -
                       origin_matrix[1][0] * origin_matrix[0][1];
        } else {
            double **temp_matrix = init_empty(rows - 1, cols - 1, err);
            if (*err != 0) {
                temp_det = 0;
            } else {
                int sign = 1;

                for (int i = 0; i < rows; ++i) {
                    minus_row_col(origin_matrix, temp_matrix, i, 0, rows);
                    temp_det = temp_det + sign * origin_matrix[i][0] *
                                          recursive_det(temp_matrix, rows - 1, cols - 1, err);
                    sign = -sign;
                }
            }
            clear_matrix(temp_matrix, rows - 2);
        }
    }

    return(temp_det);
}

double** mul_scalar(double** matrix, int rows, int cols, double val, int* err) {
    double** temp_matrix = init_empty(rows, cols, err);
    if (*err == ERR) {
        temp_matrix = NULL;
    } else {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                temp_matrix[i][j] = matrix[i][j] * val;
            }
        }
    }
    return temp_matrix;
}

double** adj(double** matrix, int rows, int cols, int* err) {
    double** temp_matrix = NULL;
    if (rows != cols) {
        *err = ERR;
    } else {
        temp_matrix = init_empty(rows, cols, err);
        if (*err != ERR) {
            int sign;

            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    double **additions_matrix = init_empty(rows - 1, cols - 1, err);
                    if (*err == ERR) {
                        temp_matrix = clear_matrix(temp_matrix, rows - 1);
                    } else {
                        minus_row_col(matrix, additions_matrix, j, i, rows);
                        if ((i + j) % 2 == 0) {
                            sign = 1;
                        } else {
                            sign = -1;
                        }
                        temp_matrix[i][j] = sign * recursive_det(additions_matrix, rows - 1, cols - 1, err);
                    }
                    clear_matrix(additions_matrix, rows - 2);
                }
            }
        }
    }
    return temp_matrix;
}

double** invert(double** matrix, int rows, int cols, int* err) {
    double** temp_matrix = NULL;

    if (rows != cols) {
        *err = ERR;
    } else {
        double temp_det = recursive_det(matrix, rows, cols, err);
        if (*err != ERR) {
            if (cols == 1) {
                temp_matrix = init_empty(1, 1, err);
                if (*err != ERR) {
                    if (matrix[0][0] == 0) {
                        *err = ERR;
                    } else {
                        temp_matrix[0][0] = 1 / matrix[0][0];
                    }
                }
            } else {
                double **adj_temp = adj(matrix, rows, cols, err);
                if (*err != ERR) {
                    temp_matrix = mul_scalar(adj_temp, rows, cols, (1 / temp_det), err);
                    clear_matrix(adj_temp, rows - 1);
                }
            }
        }
    }
    return temp_matrix;
}

