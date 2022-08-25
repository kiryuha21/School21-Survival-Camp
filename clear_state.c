#include <stdio.h>

#include "utils.h"

int main() {
    FILE* file = NULL;
    char* filename = get_string();
    if (filename != NULL) {
        char* first_date = get_string();
        if (first_date != NULL) {
            if (is_valid_date(first_date)) {
                int first_year, first_month, first_day;
                convert_date(first_date, &first_year, &first_month, &first_day);
                char* second_date = get_string();
                if (second_date != NULL) {
                    if (is_valid_date(second_date)) {
                        int second_year, second_month, second_day;
                        convert_date(second_date, &second_year, &second_month, &second_day);
                        if (clear_interval(file, filename,
                                           first_year, first_month, first_day,
                                           second_year, second_month, second_day) != 0) {
                            handle_error();
                        } else {
                            file = fopen(filename, "rb");
                            if (file != NULL) {
                                output_struct_file(file);
                            } else {
                                handle_error();
                            }
                        }
                    } else {
                        handle_error();
                    }
                } else {
                    handle_error();
                }
                clear_string(&second_date);
            } else {
                handle_error();
            }
        } else {
            handle_error();
        }
        clear_string(&first_date);
    } else {
        handle_error();
    }

    clear_string(&filename);
    close_file(&file);

    return 0;
}
