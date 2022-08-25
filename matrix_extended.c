//
// Copyright 2022 lyradanu
//

#include <stdio.h>
#include <stdlib.h>

#define ERR -1

#define ROWS_MAX 100
#define COLS_MAX 100

#define OPTION_MIN 1
#define OPTION_MAX 4

void handle_error();
int input_params(int* option, int* rows, int* cols);
int input_static(int arr[ROWS_MAX][COLS_MAX], int rows, int cols);
int* static_max(int arr[ROWS_MAX][COLS_MAX], int rows, int cols, int* maxs, int* err);
int* static_min(int arr[ROWS_MAX][COLS_MAX], int rows, int cols, int* mins, int* err);
int** input_dynamic_1(int** arr, int rows, int cols, int* err);
int** clear_d1(int** arr, int* err, int* input_end);
int** input_dynamic_2(int** arr, int rows, int cols, int* err);
int** clear_d2(int** arr, int* err, int* input_end, int row);
int** input_dynamic_3(int** arr, int rows, int cols, int* err);
int** common_input(int** arr, int* optional_arr, int rows, int cols, int* err, int option);
int* dynamic_max(int** arr, int rows, int cols, int* maxs, int* err);
int* dynamic_min(int** arr, int rows, int cols, int* mins, int* err);
int** clear_d3(int** arr, int* full_arr, int* err, int* input_end);
void output_static(int arr[ROWS_MAX][COLS_MAX], int rows, int cols, int* mins, int* maxs);
void output_dynamic(int** arr, int rows, int cols, int* mins, int* maxs);
void output_minmax(int* maxs, int* mins, int rows, int cols);
int** choose_and_clear(int** arr, int* optional_arr, int* err, int* input_end, const int row, int option);

int main() {
    int option, rows, cols;
    if (input_params(&option, &rows, &cols) != 0) {
        handle_error();
    } else {
        int* mins = NULL;
        int* maxs = NULL;
        int err = 0;
        if (option == 1) {
            int arr[ROWS_MAX][COLS_MAX];
            if (input_static(arr, rows, cols) == ERR) {
                handle_error();
            } else {
                mins = static_min(arr, rows, cols, mins, &err);
                if (err == 0) {
                    maxs = static_max(arr, rows, cols, maxs, &err);
                    if (err == 0) {
                        output_static(arr, rows, cols, mins, maxs);
                    } else {
                        handle_error();
                    }
                } else {
                    handle_error();
                }
            }
        } else if (option >= 2 && option <= 4) {
            int** arr = NULL;
            if (option == 2) {
                arr = input_dynamic_1(arr, rows, cols, &err);
                if (err != 0) {
                    handle_error();
                } else {
                    mins = dynamic_min(arr, rows, cols, mins, &err);
                    if (err == 0) {
                        maxs = dynamic_max(arr, rows, cols, maxs, &err);
                        if (err == 0) {
                            output_dynamic(arr, rows, cols, mins, maxs);
                        } else {
                            handle_error();
                        }
                    } else {
                        handle_error();
                    }
                }
            } else if (option == 3) {
                arr = input_dynamic_2(arr, rows, cols, &err);
                if (err != 0) {
                    handle_error();
                } else {
                    mins = dynamic_min(arr, rows, cols, mins, &err);
                    if (err == 0) {
                        maxs = dynamic_max(arr, rows, cols, maxs, &err);
                        if (err == 0) {
                            output_dynamic(arr, rows, cols, mins, maxs);
                        } else {
                            handle_error();
                        }
                    } else {
                        handle_error();
                    }
                    for (int i = 0; i < rows; ++i) {
                        free(arr[i]);
                    }
                }
            } else {
                arr = input_dynamic_3(arr, rows, cols, &err);
                if (err != 0) {
                    handle_error();
                } else {
                    mins = dynamic_min(arr, rows, cols, mins, &err);
                    if (err == 0) {
                        maxs = dynamic_max(arr, rows, cols, maxs, &err);
                        if (err == 0) {
                            output_dynamic(arr, rows, cols, mins, maxs);
                        } else {
                            handle_error();
                        }
                    } else {
                        handle_error();
                    }
                    free(arr[0]);
                }
            }
            free(arr);
        }
        free(mins);
        free(maxs);
    }
}

void handle_error() {
    printf("n/a");
}

int input_params(int* option, int* rows, int* cols) {
    int return_code = 0;

    char sym = 0;
    int count = scanf("%d%c", option, &sym);
    if (!(count == 2 && sym == '\n' && *option >= OPTION_MIN && *option <= OPTION_MAX)) {
        return_code = ERR;
    }

    if (return_code != ERR) {
        sym = 0;
        count = scanf("%d%d%c", rows, cols, &sym);
        if (!(count == 3 && sym == '\n' && *rows > 0 && *cols > 0)) {
            return_code = ERR;
        }
        if (return_code != ERR) {
            if (*option == 1 && (*rows > ROWS_MAX || *cols > COLS_MAX)) {
                return_code = ERR;
            }
        }
    }
    return return_code;
}

int input_static(int arr[ROWS_MAX][COLS_MAX], int rows, int cols) {
    int return_code = 0;
    int input_end = 0;

    for (int i = 0; i < rows && !input_end; ++i) {
        for (int j = 0; j < cols - 1 && !input_end; ++j) {
            char sym = 0;
            if (scanf("%d%c", &arr[i][j], &sym) != 2 || sym != ' ') {
                return_code = ERR;
                input_end = 1;
            }
        }
        char sym = 0;
        int count = scanf("%d%c", &arr[i][cols - 1], &sym);
        if (!((count == 2 && sym == '\n') || (count == 1 && sym == 0))) {
            return_code = ERR;
            input_end = 1;
        }
    }
    return return_code;
}

void output_minmax(int* maxs, int* mins, int rows, int cols) {
    for (int i = 0; i < rows - 1; ++i) {
        printf("%d ", maxs[i]);
    }
    printf("%d\n", maxs[rows - 1]);

    for (int i = 0; i < cols - 1; ++i) {
        printf("%d ", mins[i]);
    }
    printf("%d", mins[rows - 1]);
}

void output_static(int arr[ROWS_MAX][COLS_MAX], int rows, int cols, int* mins, int* maxs) {
    for (int i = 0; i < rows - 1; ++i) {
        for (int j = 0; j < cols - 1; ++j) {
            printf("%d ", arr[i][j]);
        }
        printf("%d\n", arr[i][cols - 1]);
    }

    for (int i = 0; i < cols - 1; ++i) {
        printf("%d ", arr[rows - 1][i]);
    }
    printf("%d\n", arr[rows - 1][cols - 1]);

    output_minmax(maxs, mins, rows, cols);
}

int* static_max(int arr[ROWS_MAX][COLS_MAX], int rows, int cols, int* maxs, int* err) {
    *err = 0;
    maxs = (int*)calloc(rows, sizeof(int));
    if (maxs == NULL) {
        *err = ERR;
    } else {
        for (int i = 0; i < rows; ++i) {
            int max = arr[i][0];
            for (int j = 1; j < cols; ++j) {
                if (arr[i][j] > max) {
                    max = arr[i][j];
                }
            }
            maxs[i] = max;
        }
    }
    return maxs;
}

int* static_min(int arr[ROWS_MAX][COLS_MAX], int rows, int cols, int* mins, int* err) {
    *err = 0;
    mins = (int*)calloc(cols, sizeof(int));
    if (mins == NULL) {
        *err = ERR;
    } else {
        for (int i = 0; i < cols; ++i) {
            int min = arr[0][i];
            for (int j = 1; j < rows; ++j) {
                if (arr[j][i] < min) {
                    min = arr[j][i];
                }
            }
            mins[i] = min;
        }
    }
    return mins;
}

int* dynamic_max(int** arr, int rows, int cols, int* maxs, int* err) {
    *err = 0;
    maxs = (int*)calloc(rows, sizeof(int));
    if (maxs == NULL) {
        *err = ERR;
    } else {
        for (int i = 0; i < rows; ++i) {
            int max = arr[i][0];
            for (int j = 1; j < cols; ++j) {
                if (arr[i][j] > max) {
                    max = arr[i][j];
                }
            }
            maxs[i] = max;
        }
    }
    return maxs;
}

int* dynamic_min(int** arr, int rows, int cols, int* mins, int* err) {
    *err = 0;
    mins = (int*)calloc(cols, sizeof(int));
    if (mins == NULL) {
        *err = ERR;
    } else {
        for (int i = 0; i < cols; ++i) {
            int min = arr[0][i];
            for (int j = 1; j < rows; ++j) {
                if (arr[j][i] < min) {
                    min = arr[j][i];
                }
            }
            mins[i] = min;
        }
    }
    return mins;
}

void output_dynamic(int** arr, int rows, int cols, int* mins, int* maxs) {
    for (int i = 0; i < rows - 1; ++i) {
        for (int j = 0; j < cols - 1; ++j) {
            printf("%d ", arr[i][j]);
        }
        printf("%d\n", arr[i][cols - 1]);
    }

    for (int i = 0; i < cols - 1; ++i) {
        printf("%d ", arr[rows - 1][i]);
    }
    printf("%d\n", arr[rows - 1][cols - 1]);

    output_minmax(maxs, mins, rows, cols);
}

int** choose_and_clear(int** arr, int* optional_arr, int* err, int* input_end, const int row, int option) {
    if (option == 1) {
        arr = clear_d1(arr, err, input_end);
    } else if (option == 2) {
        arr = clear_d2(arr, err, input_end, row);
    } else {
        arr = clear_d3(arr, optional_arr, err, input_end);
    }
    return arr;
}

int** common_input(int** arr, int* optional_arr, int rows, int cols, int* err, int option) {
    int input_end = 0;
    for (int i = 0; i < rows && !input_end; ++i) {
        if (option == 2) {
            arr[i] = (int*)(calloc(cols, sizeof(int)));
            if (arr[i] == NULL) {
                arr = clear_d2(arr, err, &input_end, i);
            }
        }
        for (int j = 0; j < cols - 1 && !input_end; ++j) {
            char sym = 0;
            if (scanf("%d%c", &arr[i][j], &sym) != 2 || sym != ' ') {
                arr = choose_and_clear(arr, optional_arr, err, &input_end, i, option);
            }
        }
        if (*err == 0) {
            char sym = 0;
            int count = scanf("%d%c", &arr[i][cols - 1], &sym);
            if (!((count == 2 && sym == '\n') || (count == 1 && sym == 0))) {
                arr = choose_and_clear(arr, optional_arr, err, &input_end, i, option);
            }
        }
    }
    return arr;
}

int** clear_d1(int** arr, int* err, int* input_end) {
    free(arr);
    *err = ERR;
    *input_end = 1;
    arr = NULL;
    return arr;
}

int** input_dynamic_1(int** arr, int rows, int cols, int* err) {
    arr = (int**)(calloc(rows * cols + rows, sizeof(int*)));
    if (arr == NULL) {
        *err = ERR;
    } else {
        int *ptr = (int *) (arr + rows);

        for (int i = 0; i < rows; ++i) {
            arr[i] = ptr + cols * i;
        }

        arr = common_input(arr, NULL, rows, cols, err, 1);
    }

    return arr;
}

int** clear_d2(int** arr, int* err, int* input_end, int row) {
    *err = ERR;
    *input_end = 1;
    for (int j = row; j >= 0; --j) {
        free(arr[j]);
    }
    free(arr);
    arr = NULL;
    return arr;
}

int** input_dynamic_2(int** arr, int rows, int cols, int* err) {
    arr = (int**)(calloc(rows, sizeof(int*)));
    if (arr == NULL) {
        *err = ERR;
    } else {
        arr = common_input(arr, NULL, rows, cols, err, 2);
    }
    return arr;
}

int** clear_d3(int** arr, int* full_arr, int* err, int* input_end) {
    free(arr);
    free(full_arr);
    *err = ERR;
    *input_end = 1;
    arr = NULL;
    return arr;
}

int** input_dynamic_3(int** arr, int rows, int cols, int* err) {
    arr = (int**)(calloc(rows, sizeof(int*)));
    if (arr == NULL) {
        *err = ERR;
    } else {
        int* full_arr = (int*)(calloc(rows * cols, sizeof(int)));
        if (full_arr == NULL) {
            *err = ERR;
        } else {
            for (int i = 0; i < rows; ++i) {
                arr[i] = full_arr + cols * i;
            }

            arr = common_input(arr, full_arr, rows, cols, err, 3);
        }
    }
    return arr;
}

