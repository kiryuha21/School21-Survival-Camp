#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

#define ERR -1

int read_size(int* num);
int check_one_size(const char* line, int size);
int process_line(char* line, int size);
int process_word(char* word, int size_left, int size);

int main(int argc, char** argv) {
    if (argc == 2 && s21_strcmp(argv[1], "-w") == 0) {
        int size;
        int error = read_size(&size);
        if (error == 0) {
            char* line;
            size_t line_size;
            getline(&line, &line_size, stdin);
            if (line_size <= 101) {  // \n also counts
                line[s21_strlen(line) - 1] = '\0';
                if (process_line(line, size) == ERR) {
                    printf("n/a");
                }
            } else {
                printf("n/a");
            }
            free(line);
        } else {
            printf("n/a");
        }
    } else {
        printf("n/a");
    }
}

int read_size(int* num) {
    int return_value = 0;
    char sym = 0;
    int count = scanf("%d%c", num, &sym);
    if (!(count == 2 && *num > 0 && sym == '\n')) {
        return_value = ERR;
    }
    return return_value;
}

int check_one_size(const char* line, int size) {
    int is_sym = 0;
    int is_space = 0;
    int stop = 0;

    if (line[0] == ' ') {
        is_space = 1;
    } else {
        is_sym = 1;
    }

    for (int i = 1; i < size && !stop; ++i) {
        if (line[i] == ' ') {
            if (!is_space) {
                is_space = 0;
            }
        } else {
            if (is_sym) {
                stop = 1;
            } else {
                is_sym = 1;
            }
        }
    }
    return stop;
}

int process_line(char* line, int size) {
    int return_value = 0;

    if (size == 1) {
        if (check_one_size(line, (int)s21_strlen(line)) != 0) {
            return_value = ERR;
        }
    }

    if (return_value != ERR) {
        char *temp = s21_strtok(line, " ");
        int size_left = process_word(temp, size, size);
        int not_empty = 1;
        while (not_empty) {
            temp = s21_strtok(NULL, " ");
            if (*temp == '\0') {
                not_empty = 0;
            } else {
                size_left = process_word(temp, size_left, size);
            }
        }
    }
    return return_value;
}

int process_word(char* word, int size_left, int size) {
    int len = (int)s21_strlen(word);
    if (len <= size_left - 1 && size_left != size) {
        printf(" %s", word);
        size_left -= (len + 1);
    } else if (len <= size_left && size_left == size) {
        printf("%s", word);
        size_left -= len;
    } else if (len < size) {
        printf("\n%s", word);
        size_left = size - len;
    } else {
        if (size_left != size) {
            printf(" ");
            size_left -= 1;
        }
        while (len > size) {
            for (int i = 0; i < size_left - 1; ++i) {
                printf("%c", *word);
                ++word;
            }
            printf("-\n");
            len -= (size_left - 1);
            size_left = size;
        }
        for (int i = 0; i < len; ++i) {
            printf("%c", *word);
            ++word;
        }
        size_left = size - len;
    }

    return size_left;
}
