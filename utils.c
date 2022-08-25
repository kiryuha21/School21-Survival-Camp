#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"

int is_in_interval(int year, int month, int date,
                   int first_year, int first_month, int first_day,
                   int second_year, int second_month, int second_day) {
    size_t vt = year * 10000 + month * 100 + date;
    size_t v1 = first_year * 10000 + first_month * 100 + first_day;
    size_t v2 = second_year * 10000 + second_month * 100 + second_day;

    return vt >= v1 && vt <= v2;
}

int clear_interval(FILE* file, char* filename,
                   int first_year, int first_month, int first_day,
                   int second_year, int second_month, int second_day) {
    int return_value = 0;
    file = fopen(filename, "rb");
    if (file != NULL) {
        int size = get_records_count_in_file(file);
        if (size != 0) {
            char* temp_name = full_path(filename, "_temp");
            if (temp_name != NULL) {
                FILE* temp_file = fopen(temp_name, "wb");
                if (temp_file != NULL) {
                    int count = 0;
                    for (int i = 0; i < size; ++i) {
                        state temp = read_record_from_file(file, i);
                        if (!is_in_interval(temp.year, temp.month, temp.day,
                                            first_year, first_month, first_day,
                                            second_year, second_month, second_day)) {
                            write_record_in_file(temp_file, &temp, count);
                            ++count;
                        }
                    }

                    printf("count = %d\n", count);
                    close_file(&file);
                    close_file(&temp_file);

                    remove(filename);
                    rename(temp_name, filename);
                } else {
                    return_value = ERR;
                }
                free(temp_name);
            } else {
                return_value = ERR;
            }
        } else {
            return_value = ERR;
        }
    } else {
        return_value = ERR;
    }

    return return_value;
}

char* full_path(char* dir, char* name) {
    size_t size = strlen(dir) + strlen(name) + 1;
    char* result = (char*) calloc(size, sizeof(char));
    if (result != NULL) {
        result = strcat(result, dir);
        result = strcat(result, name);
        result[size - 1] = '\0';
    }
    return result;
}


int is_digit(char ch) {
    return ch >= '0' && ch <= '9';
}

int is_valid_date(const char* date) {
    return is_digit(*date) && is_digit(*(date + 1)) && *(date + 2) == '.' &&
           is_digit(*(date + 3)) && is_digit(*(date + 4)) && *(date + 5) == '.' &&
           is_digit(*(date + 6)) && is_digit(*(date + 7)) &&
           is_digit(*(date + 8)) && is_digit(*(date + 9));
}

void convert_date(char* datestring, int* year, int* month, int* day) {
    *day = atoi(datestring);
    datestring += 3;
    *month = atoi(datestring);
    datestring += 3;
    *year = atoi(datestring);
}

state input_state(int* err) {
    state result;

    char sym = 0;
    int count = scanf("%d%d%d%d%d%d%d%d%c", &result.year, &result.month, &result.day,
                      &result.hour, &result.minute, &result.second,
                      &result.status, &result.code, &sym);
    if ((count == 9 && sym == '\n') || (count == 8 && sym == 0)) {
        if (result.status != 0 && result.status != 1) {
            *err = ERR;
        }
    } else {
        *err = ERR;
    }

    return result;
}

void sort_binary(FILE* file) {
    int size = get_records_count_in_file(file);
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            state first = read_record_from_file(file, j);
            state second = read_record_from_file(file, j + 1);
            if (compare(first, second)) {
                swap_records_in_file(file, j, j + 1);
            }
        }
    }
}

int compare(state first, state second) {
    int return_value = 0;
    if (first.year > second.year) {
        return_value = 1;
    } else if (first.year == second.year) {
        if (first.month > second.month) {
            return_value = 1;
        } else if (first.month == second.month) {
            if (first.day > second.day) {
                return_value = 1;
            } else if (first.day == second.day) {
                if (first.hour > second.hour) {
                    return_value = 1;
                } else if (first.hour == second.hour) {
                    if (first.minute > second.minute) {
                        return_value = 1;
                    } else if (first.minute == second.minute) {
                        if (first.second == second.second) {
                            return_value = 1;
                        }
                    }
                }
            }
        }
    }
    return return_value;
}

void output_struct_file(FILE* file) {
    int size = get_records_count_in_file(file);
    for (int i = 0; i < size - 1; ++i) {
        state temp = read_record_from_file(file, i);
        printf("%d %d %d %d %d %d %d %d\n", temp.year, temp.month, temp.day, temp.hour,
               temp.minute, temp.second, temp.status, temp.code);
    }
    state temp = read_record_from_file(file, size - 1);
    printf("%d %d %d %d %d %d %d %d", temp.year, temp.month, temp.day, temp.hour,
           temp.minute, temp.second, temp.status, temp.code);
}

state read_record_from_file(FILE *pfile, int index) {
    int offset = index * sizeof(state);
    fseek(pfile, offset, SEEK_SET);

    state record;
    fread(&record, sizeof(state), 1, pfile);

    // For safety reasons, we return the file position pointer to the beginning of the file.
    rewind(pfile);

    // Return read record
    return record;
}

int get_file_size_in_bytes(FILE *pfile) {
    int size;
    fseek(pfile, 0, SEEK_END);  // Move the position pointer to the end of the file.
    size = ftell(pfile);  // number of bites from the beginning
    rewind(pfile);
    return size;
}

int get_records_count_in_file(FILE *pfile) {
    return get_file_size_in_bytes(pfile) / sizeof(state);
}

void write_record_in_file(FILE *pfile, const state *record_to_write, int index) {
    int offset = index * sizeof(state);
    fseek(pfile, offset, SEEK_SET);

    // Write a record of the specified type to a file.
    fwrite(record_to_write, sizeof(state), 1, pfile);

    // Just in case, force the I/O subsystem to write the contents of its buffer to a file right now.
    fflush(pfile);

    // For safety reasons, return the file position pointer to the beginning of the file.
    rewind(pfile);
}

void swap_records_in_file(FILE *pfile, int record_index1, int record_index2) {
    // Read both records from file to variables
    state record1 = read_record_from_file(pfile, record_index1);
    state record2 = read_record_from_file(pfile, record_index2);

    // Rewrite records in file
    write_record_in_file(pfile, &record1, record_index2);
    write_record_in_file(pfile, &record2, record_index1);
}

char* get_string() {
    char* filename = NULL;
    size_t size;
    getline(&filename, &size, stdin);
    filename[strlen(filename) - 1] = '\0';
    return filename;
}

int first_entry(FILE** file, char* filename, int year, int month, int day) {
    int return_value = 0;
    *file = fopen(filename, "rb");
    if (*file != NULL) {
        int size = get_records_count_in_file(*file);
        int found = 0;
        for (int i = 0; !found && i < size; ++i) {
            state temp = read_record_from_file(*file, i);
            if (temp.year == year && temp.month == month && temp.day == day) {
                printf("%d", temp.code);
                found = 1;
            }
        }
        if (!found) {
            printf("n/a");
        }
    } else {
        return_value = ERR;
    }
    return return_value;
}

void close_file(FILE** file) {
    if (*file != NULL) {
        fclose(*file);
        *file = NULL;
    }
}

void clear_string(char** line) {
    if (*line != NULL) {
        free(*line);
        *line = NULL;
    }
}

void handle_error() {
    printf("n/a\n");
}

void flush_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int read_option(int* option) {
    char sym;
    int return_value = 0;
    int count = scanf("%d%c", option, &sym);
    if (count != 2 || sym != '\n') {
        flush_stdin();
        return_value = ERR;
    } else if (*option != 1 && *option != 2 && *option != 0) {
        return_value = ERR;
    }
    return return_value;
}
