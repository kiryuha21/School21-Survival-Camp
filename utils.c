#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

void flush_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int get_file_size_in_bytes(FILE *pfile) {
    int size;
    fseek(pfile, 0, SEEK_END);  // Move the position pointer to the end of the file.
    size = ftell(pfile);  // number of bites from the beginning
    rewind(pfile);
    return size;
}

void clear_ints(int** arr) {
    if (*arr != NULL) {
        free(*arr);
        *arr = NULL;
    }
}

int* empty_or_positive_array(int* size) {
    int* result = NULL;
    char* string_number = get_string();
    char* start = string_number;
    if (string_number != NULL) {
        *size = 0;
        int capacity = 1;
        result = (int*) calloc(capacity, sizeof(int));
        if (string_number[0] == '\0') {
            result[0] = -1;
        } else {
            int stop = 0;
            while (!stop) {
                char* end;
                result[*size] = (int)strtol(string_number, &end, 10);
                ++(*size);
                if (*size == capacity) {
                    capacity *= 2;
                    int* temp = (int*) realloc(result, capacity);
                    if (temp != NULL) {
                        result = temp;
                    } else {
                        free(result);
                        result = NULL;
                    }
                }
                if ((result != NULL && result[*size - 1] < 0) || (*end != '\0' && *end != ' ')) {
                    free(result);
                    result = NULL;
                    stop = 1;
                } else if (*end == ' ') {
                    string_number += (end - string_number + 1);
                } else {
                    stop = 1;
                }
            }
        }
    }
    clear_string(&start);
    return result;
}

void close_file(FILE** file) {
    if (*file != NULL) {
        fclose(*file);
        *file = NULL;
    }
}

char* get_string() {
    char* filename = NULL;
    size_t size;
    getline(&filename, &size, stdin);
    filename[strlen(filename) - 1] = '\0';
    return filename;
}

void clear_string(char** line) {
    if (*line != NULL) {
        free(*line);
        *line = NULL;
    }
}
