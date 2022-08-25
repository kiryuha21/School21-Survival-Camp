#include <stdlib.h>
#include <stdio.h>

#include "data_process.h"
#include "data_io.h"

int main() {
    double *data = NULL;
    int n;

    data = input(&n);
    if (data != NULL) {
        if (normalization(data, n)) {
            output(data, n);
        } else {
            printf("ERROR");
        }
        free(data);
    } else {
        printf("n/a");
    }
    return 0;
}
