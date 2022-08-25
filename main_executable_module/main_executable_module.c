#include <stdio.h>
#include <stdlib.h>

#ifdef DIN
#include <dlfcn.h>
#endif

#ifdef MACRO
#include "data_io_macro.h"
#else
#include "data_io.h"
#endif

#include "data_process.h"
#include "decision.h"

int main() {
    int lib_found = 1;
#ifdef DIN
    void* head = dlopen("libdata_process.so", RTLD_LAZY);
    if (!head) {
        lib_found = 0;
    }
    int (*normalization)(double *data, int n) = dlsym(head, "normalization");
    void (*sort)(double* data, int first, int last) = dlsym(head, "sort");
#endif
    if (!lib_found) {
        printf("Dynamic library not found!");
    } else {
        double *data = NULL;
        int n;

        printf("LOAD DATA...\n");
        data = input(&n);
        if (data != NULL) {
            printf("RAW DATA:\n\t");
            output(data, n);

            printf("\nNORMALIZED DATA:\n\t");
            if (normalization(data, n)) {
                output(data, n);
                printf("\nSORTED NORMALIZED DATA:\n\t");
                sort(data, 0, n - 1);
                output(data, n);

                printf("\nFINAL DECISION:\n\t");
                if (make_decision(data, n)) {
                    printf("YES");
                } else {
                    printf("NO");
                }
            } else {
                printf("ERROR");
            }

            free(data);
        } else {
            printf("n/a");
        }
    }
#ifdef DIN
    dlclose(head);
#endif
    return 0;
}
