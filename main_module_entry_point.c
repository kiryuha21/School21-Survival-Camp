#include <stdio.h>
#include <stdlib.h>

#include "print_module.h"

#ifdef DOC
#include "documentation_module.h"
#endif

int main() {
    print_log(print_char, Module_load_success_message);

#ifdef DOC
    int* availability_mask = check_available_documentation_module(validate, Documents_count, Documents);
    if (availability_mask != NULL) {
        char* documents[] = {Documents};
        for (int i = 0; i < Documents_count - 1; ++i) {
            printf("%-15s : %s\n", documents[i], availability_mask[i] == 1 ? "available" : "unavailable");
        }
        printf("%-15s : %s\n", documents[Documents_count - 1],
                            availability_mask[Documents_count - 1] == 1 ? "available" : "unavailable");
        free(availability_mask);
    } else {
        printf("n/a");
    }
#endif

    return 0;
}
