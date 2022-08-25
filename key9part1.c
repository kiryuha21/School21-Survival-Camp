//
// Copyright 2022 lyradanu
//

/*------------------------------------
	Здравствуй, человек!
	Чтобы получить ключ 
	поработай с комментариями.
-------------------------------------*/

#include <stdio.h>

#define ERR -1

#define NMAX 10

int input(int *buffer, int *length);
void output(int *buffer, int length);
void output_num(int num);
int sum_numbers(const int *buffer, int length);
int find_numbers(const int* buffer, int length, int number, int* numbers);
void handle_error();

/*------------------------------------
	Функция получает массив данных 
	через stdin.
	Выдает в stdout особую сумму
	и сформированный массив 
	специальных элементов
	(выбранных с помощью найденной суммы):
	это и будет частью ключа
-------------------------------------*/
int main() {
    int n, data[NMAX];
    if (input(data, &n) == ERR) {
        handle_error();
    } else {
        int sum = sum_numbers(data, n);
        if (sum == 1) {
            handle_error();
        } else {
            int res_arr[NMAX];
            output_num(sum);
            int length = find_numbers(data, n, sum, res_arr);
            output(res_arr, length);
        }
    }
    return 0;
}

void output_num(int num) {
    printf("%d\n", num);
}

void handle_error() {
    printf("n/a");
}

/*------------------------------------
	Функция должна находить
	сумму четных элементов 
	с 0-й позиции.
-------------------------------------*/
int sum_numbers(const int *buffer, int length) {
    int sum = 0;
    int found = 0;

    for (int i = 0; i < length; i++) {
        if (buffer[i] % 2 == 0) {
            sum = sum + buffer[i];
            found = 1;
        }
    }

    if (found == 0) {
        sum = 1;
    }
    return sum;
}

/*------------------------------------
	Функция должна находить
	все элементы, на которые нацело
	делится переданное число и
	записывает их в выходной массив.
-------------------------------------*/
int find_numbers(const int* buffer, int length, int number, int* numbers) {
    int arr_pos = 0;
    for (int i = 0; i < length; ++i) {
        if (buffer[i] != 0 && number % buffer[i] == 0) {
            numbers[arr_pos] = buffer[i];
            ++arr_pos;
        }
    }
    return arr_pos;
}

int input(int *a, int *n) {
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
            count = scanf("%d%c", (a + *n - 1), &sym);
            if (!((count == 1 && sym == 0) || (count == 2 && sym == '\n'))) {
                return_code = ERR;
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

