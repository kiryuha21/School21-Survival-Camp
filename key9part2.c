#include <stdio.h>

#define ERR -1

#define LEN 100

void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);
void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);
void operation(const int *buff1, int len1, const int *buff2, int len2, int *result, int *result_length);
void make_sign(int* arr, int start, int sign);
void negative_leading(int* arr, int length);
int abs(int num);
int input(int* a, int* start);
void compare(int* first, int* second, int len1, int len2, int* res);
void output(int* a, int start);
void handle_error();
void print_line();

/*
    Беззнаковая целочисленная длинная арифметика
    с использованием массивов.
    Ввод: 
     * 2 длинных числа в виде массивов до 100 элементов
     * В один элемент массива нельзя вводить число > 9
    Вывод: 
     * Результат сложения и разности чисел-массивов
    Пример:
     * 1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 6 1
       2 9

       1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 9 0
       1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 3 2
*/
int main() {
    int first[LEN];
    int first_start = LEN;
    if (input(first, &first_start) == ERR) {
        handle_error();
    } else {
        int second[LEN];
        int second_start = LEN;
        if (input(second, &second_start) == ERR) {
            handle_error();
        } else {
            int sum_arr[LEN + 1];
            int sum_start;
            sum(first, first_start, second, second_start, sum_arr, &sum_start);
            output(sum_arr, sum_start);

            print_line();

            int res = 0;
            compare(first, second, first_start, second_start, &res);
            if (res == 2) {
                handle_error();
            } else {
                int sub_arr[LEN + 1];
                int sub_start;
                sub(first, first_start, second, second_start, sub_arr, &sub_start);
                output(sub_arr, sub_start);
            }
        }
    }
    return 0;
}

void compare(int* first, int* second, int len1, int len2, int* res) {
    *res = 0;
    if (len1 < len2) {
        *res = 1;
    } else if (len2 < len1) {
        *res = 2;
    } else {
        int end_cycle = 0;
        for (int i = LEN - 1; i >= len1 && !end_cycle; --i) {
            if (abs(first[i]) > abs(second[i])) {
                *res = 1;
                end_cycle = 1;
            } else if (abs(first[i]) < abs(second[i])) {
                *res = 2;
                end_cycle = 1;
            }
        }
    }
}

void print_line() {
    puts("");
}

void handle_error() {
    printf("n/a");
}

int abs(int num) {
    int res = num;
    if (num < 0) {
        res = -num;
    }
    return res;
}

void make_sign(int* arr, int start, int sign) {
    for (int i = start; i < LEN; ++i) {
        if (sign == -1) {
            arr[i] = -abs(arr[i]);
        } else {
            arr[i] = abs(arr[i]);
        }
    }
}

void operation(const int *buff1, int len1, const int *buff2, int len2, int *result, int *result_length) {
    result[LEN] = 0;
    int first_bigger = len1 < len2 ? 1 : 0;
    int res_start = first_bigger ? len1 : len2;
    int overload = 0;
    *result_length = res_start;

    for (int i = len1, j = len2, ind = res_start; i < LEN && j < LEN; ++i, ++j, ++ind) {
        int full_sum = buff1[i] + buff2[j] + overload;
        if (full_sum >= 10) {
            result[ind] = full_sum % 10;
            overload = 1;
        } else if (full_sum < 0) {
            result[ind] = 10 + full_sum;
            overload = -1;
        } else {
            result[ind] = full_sum;
            overload = 0;
        }
    }

    int start;
    if (first_bigger) {
        start = len1 + LEN - len2;
        for (int i = start; i < LEN; ++i) {
            if (overload != 0) {
                int full_sum = buff1[i] + overload;
                if (full_sum >= 10) {
                    result[i] = full_sum % 10;
                    overload = 1;
                } else if (full_sum < 0) {
                    result[i] = 10 + full_sum;
                    overload = -1;
                } else {
                    result[i] = full_sum;
                    overload = 0;
                }
            } else {
                result[i] = buff1[i];
            }
        }
    } else {
        start = len2 + LEN - len1;
        for (int i = start; i < LEN; ++i) {
            if (overload != 0) {
                int full_sum = buff2[i] + overload;
                if (full_sum >= 10) {
                    result[i] = full_sum % 10;
                    overload = 1;
                } else if (full_sum < 0) {
                    result[i] = 10 + full_sum;
                    overload = -1;
                } else {
                    result[i] = full_sum;
                    overload = 0;
                }
            } else {
                result[i] = buff2[i];
            }
        }
    }

    if (overload != 0) {
        result[LEN] += overload;
    }
}

void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length) {
    buff2[LEN - 1] = -buff2[LEN - 1];
    sum(buff1, len1, buff2, len2, result, result_length);
    buff2[LEN - 1] = -buff2[LEN - 1];
}

void negative_leading(int* arr, int length) {
    for (int i = LEN; i >= length; --i) {
        if (arr[i] != 0) {
            arr[i] = -arr[i];
            return;
        }
    }
}

void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length) {
    int sign1 = buff1[LEN - 1] < 0 ? -1 : 1;
    int sign2 = buff2[LEN - 1] < 0 ? -1 : 1;
    if (sign1 == sign2) {
        buff1[LEN - 1] = abs(buff1[LEN - 1]);
        buff2[LEN - 1] = abs(buff2[LEN - 1]);
        operation(buff1, len1, buff2, len2, result, result_length);
        if (sign1 == -1) {
            negative_leading(result, *result_length);
            buff1[LEN - 1] = -buff1[LEN - 1];
            buff2[LEN - 1] = -buff2[LEN - 1];
        }
    } else {
        if (sign1 == -1) {
            int res = 0;
            compare(buff1, buff2, len1, len2, &res);
            if (res == 1) {
                make_sign(buff1, len1, 1);
                make_sign(buff2, len2, -1);
                operation(buff1, len1, buff2, len2, result, result_length);
                make_sign(buff2, len2, 1);
                negative_leading(result, *result_length);
            } else {
                make_sign(buff1, len1, -1);
                operation(buff1, len1, buff2, len2, result, result_length);
                make_sign(buff1, len1, 1);
            }

            buff1[LEN - 1] = -buff1[LEN - 1];
        } else {
            int res = 0;
            compare(buff1, buff2, len1, len2, &res);
            if (res == 2) {
                make_sign(buff1, len1, -1);
                make_sign(buff2, len2, 1);
                operation(buff2, len2, buff1, len1, result, result_length);
                make_sign(buff1, len1, 1);
                negative_leading(result, *result_length);
            } else {
                make_sign(buff2, len2, -1);
                operation(buff1, len1, buff2, len2, result, result_length);
                make_sign(buff2, len2, 1);
            }

            buff2[LEN - 1] = -buff2[LEN - 1];
        }
    }
}

int input(int* a, int* start) {
    int return_code = 0;
    int zero_start = 1;
    int input_end = 0;
    for (int i = 0; i < LEN && !input_end; ++i) {
        int ind = LEN - i - 1;
        char sym = 0;
        int count = scanf("%d%c", &a[ind], &sym);
        if (a[ind] != 0) {
            zero_start = 0;
        }
        if (!(zero_start && a[ind] == 0)) {
            --(*start);
        } else {
            --i;
        }

        if (count != 2) {
            if (!(count == 1 && sym == 0)) {
                return_code = ERR;
                input_end = 1;
            }
        }

        // if count == 2
        if (return_code != ERR) {
            if (!((sym == ' ' || sym == '\n') && a[ind] <= 9 && (a[ind] >= 0 || (i == 0 && a[ind] >= -9)))) {
                return_code = ERR;
                input_end = 1;
            }
            if (return_code != ERR) {
                if (sym == '\n') {
                    input_end = 1;
                }
            }
        }
    }
    return return_code;
}

void output(int* a, int start) {
    int num_start = 0;
    for (int i = LEN; i > start; --i) {
        if (a[i] != 0) {
            num_start = 1;
            printf("%d ", a[i]);
        } else if (num_start) {
            printf("%d ", 0);
        }
    }

    if (a[start] != 0) {
        num_start = 1;
        printf("%d", a[start]);
    } else if (num_start) {
        printf("%d", 0);
    }

    if (!num_start) {
        printf("%d", 0);
    }
}
