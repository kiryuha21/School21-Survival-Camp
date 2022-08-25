//
// Copyright 2022 lyradanu
//

#include <stdio.h>
#include <stdlib.h>

#define ERR -1

#define OPTION_MIN 1
#define OPTION_MAX 3

int** input(int **matrix, int *n, int *m, int* err);
void output(int **matrix, int n, int m);
int** sum(int **matrix_first, int n_first, int m_first, int **matrix_second,
    int n_second, int m_second, int *n_result, int *m_result, int* err);
int** transpose(int **matrix, int n, int m, int* err);
int** mul(int **matrix_first, int n_first, int m_first, int **matrix_second,
    int n_second, int m_second, int *n_result, int *m_result, int* err);
int** init_empty(int rows, int cols, int* err);
int input_option(int* option);
int input_size(int* rows, int* cols);
void handle_error();
int** clear_and_stop(int** arr, int* err, int* input_end, int row);
int** clear_matrix(int** arr, int rows);

int main() {
    int option;
    int err = input_option(&option);
    if (err == 0) {
        int** matrix1 = NULL;
        int** matrix2 = NULL;
        int** res_matrix = NULL;
        int rows, cols;
        int rows2, cols2;
        int rows_res = -1, cols_res = -1;
        matrix1 = input(matrix1, &rows, &cols, &err);
        if (err == 0) {
            if (option == 1) {  // sum
                matrix2 = input(matrix2, &rows2, &cols2, &err);
                if (err == 0) {
                    res_matrix = sum(matrix1, rows, cols, matrix2,
                                     rows2, cols2, &rows_res, &cols_res, &err);
                    if (err == 0) {
                        output(res_matrix, rows_res, cols_res);
                    } else {
                        handle_error();
                    }
                } else {
                    handle_error();
                }
                clear_matrix(res_matrix, rows_res - 1);
            } else if (option == 2) {  // mul
                matrix2 = input(matrix2, &rows2, &cols2, &err);
                if (err == 0) {
                    res_matrix = mul(matrix1, rows, cols, matrix2,
                                     rows2, cols2, &rows_res, &cols_res, &err);
                    if (err == 0) {
                        output(res_matrix, rows_res, cols_res);
                    } else {
                        handle_error();
                    }
                } else {
                    handle_error();
                }
                clear_matrix(res_matrix, rows_res - 1);
            } else {  // transp
                res_matrix = transpose(matrix1, rows, cols, &err);
                if (err == 0) {
                    output(res_matrix, cols, rows);
                } else {
                    handle_error();
                }
                clear_matrix(res_matrix, cols - 1);
            }
        } else {
            handle_error();
        }
        clear_matrix(matrix1, rows - 1);
        clear_matrix(matrix2, rows - 1);
    } else {
        handle_error();
    }
    return 0;
}

void output(int** matrix, int n, int m) {
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

void handle_error() {
    printf("n/a");
}

int input_option(int* option) {
    int return_code = 0;

    char sym = 0;
    int count = scanf("%d%c", option, &sym);
    if (!(count == 2 && sym == '\n' && *option >= OPTION_MIN && *option <= OPTION_MAX)) {
        return_code = ERR;
    }
    return return_code;
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

int** clear_and_stop(int** arr, int* err, int* input_end, int row) {
    *err = ERR;
    *input_end = 1;
    clear_matrix(arr, row);
    arr = NULL;
    return arr;
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
    if (*err != 0) {
        matrix = NULL;
    }
    return matrix;
}

int** sum(int **matrix_first, int n_first, int m_first, int **matrix_second,
          int n_second, int m_second, int *n_result, int *m_result, int* err) {
    int** result = NULL;
    if (n_first != n_second || m_first != m_second) {
        *err = ERR;
    } else {
        *n_result = n_first;
        *m_result = m_first;
        result = init_empty(n_first, m_first, err);
        if (*err == 0) {
            for (int i = 0; i < n_first; ++i) {
                for (int j = 0; j < m_first; ++j) {
                    result[i][j] = matrix_first[i][j] + matrix_second[i][j];
                }
            }
        }
    }
    return result;
}

int** mul(int **matrix_first, int n_first, int m_first, int **matrix_second,
          int n_second, int m_second, int *n_result, int *m_result, int* err) {
    int** result = NULL;
    if (m_first != n_second) {
        *err = ERR;
    } else {
        *n_result = n_first;
        *m_result = m_second;

        result = init_empty(*n_result, *m_result, err);
        if (*err == 0) {
            for (int i = 0; i < n_first; ++i) {
                for (int j = 0; j < m_second; ++j) {
                    result[i][j] = 0;
                    for (int k = 0; k < m_first; ++k)
                        result[i][j] += matrix_first[i][k] * matrix_second[k][j];
                }
            }
        }
    }
    return result;
}

int** transpose(int **matrix, int n, int m, int* err) {
    int** res = NULL;
    if (matrix == NULL) {
        *err = ERR;
    } else {
        res = init_empty(m, n, err);
        if (*err == 0) {
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    res[i][j] = matrix[j][i];
                }
            }
        }
    }
    return res;
}


