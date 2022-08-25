#include <stdio.h>
#include <string.h>

#include "utils.h"

int option_0(FILE** file, char* filename);
int option_1(FILE** file, char* filename);
int option_2(FILE** file, char* filename);

int main() {
    FILE* file = NULL;
    char* filename = NULL;

    filename = get_string();
    if (filename != NULL) {
        int option;
        if (read_option(&option) == 0) {
            if (option == 0) {
                if (option_0(&file, filename) != 0) {
                    handle_error();
                }
            } else if (option == 1) {
                if (option_1(&file, filename) != 0) {
                    handle_error();
                }
            } else if (option == 2) {
                if (option_2(&file, filename) != 0) {
                    handle_error();
                }
            }
        } else {
            handle_error();
        }
    } else {
        handle_error();
    }

    clear_string(&filename);
    close_file(&file);

    return 0;
}

int option_0(FILE** file, char* filename) {
    int return_value = 0;
    *file = fopen(filename, "rb");
    if (*file == NULL) {
        return_value = ERR;
    } else {
        if (get_records_count_in_file(*file) == 0) {
            return_value = ERR;
        } else {
            output_struct_file(*file);
        }
    }
    return return_value;
}

int option_1(FILE** file, char* filename) {
    int return_value = 0;
    *file = fopen(filename, "rb+");
    if (*file == NULL) {
        return_value = ERR;
    } else {
        if (get_records_count_in_file(*file) == 0) {
            return_value = ERR;
        } else {
            sort_binary(*file);
            output_struct_file(*file);
        }
    }
    return return_value;
}

int option_2(FILE** file, char* filename) {
    int return_value = 0;
    *file = fopen(filename, "ab+");
    if (*file == NULL) {
        return_value = ERR;
    } else {
        state temp = input_state(&return_value);
        if (return_value == 0) {
            int size = get_records_count_in_file(*file);
            write_record_in_file(*file, &temp, size);

            close_file(file);
            *file = fopen(filename, "rb+");
            if (*file != NULL) {
                sort_binary(*file);
                output_struct_file(*file);
            } else {
                return_value = ERR;
            }
        }
    }
    return return_value;
}
