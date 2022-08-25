#include <stdarg.h>
#include <stdlib.h>

#include "documentation_module.h"

int validate(char* data) {
    int validation_result = !strcmp(data, Available_document);
    return validation_result;
}

int* check_available_documentation_module(int(*validate)(char*), int document_count, ...) {
    va_list arguments;
    va_start(arguments, document_count);

    int* result_arr = (int*) calloc(document_count, sizeof(int));
    if (result_arr != NULL) {
        for (int i = 0; i < document_count; ++i) {
            result_arr[i] = validate(va_arg(arguments, char*));
        }
        va_end(arguments);
    }

    return result_arr;
}
