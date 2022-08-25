#include <stdio.h>

#include "utils.h"

int main() {
    FILE* file = NULL;
    char* filename = get_string();
    if (filename != NULL) {
        char* date = get_string();
        if (date != NULL) {
            if (is_valid_date(date)) {
                int year, month, day;
                convert_date(date, &year, &month, &day);
                if (first_entry(&file, filename, year, month, day) != 0) {
                    handle_error();
                }
            } else {
                handle_error();
            }
        } else {
            handle_error();
        }
        clear_string(&date);
    } else {
        handle_error();
    }

    clear_string(&filename);
    close_file(&file);

    return 0;
}
