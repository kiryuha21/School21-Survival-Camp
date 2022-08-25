#include <stdio.h>
#include <stdlib.h>

#include "data_io.h"

double* input(int *n) {
    double* res = NULL;

    char ch = 0;
    int count = scanf("%d%c", n, &ch);
    if (count == 2 && ch == '\n' && *n > 0) {
        res = (double*)calloc(*n, sizeof(double));
        if (res != NULL) {
            int cycle_end = 0;
            for (int i = 0; i < *n - 1 && !cycle_end; ++i) {
                ch = 0;
                count = scanf("%lf%c", &res[i], &ch);
                if (count != 2 || ch != ' ') {
                    free(res);
                    res = NULL;
                    cycle_end = 1;
                }
            }
            ch = 0;
            count = scanf("%lf%c", &res[*n - 1], &ch);
            if (!((count == 2 && ch == '\n') || (count == 1 && ch == 0))) {
                free(res);
                res = NULL;
            }
        }
    }
    return res;
}

void output(double *data, int n) {
    for (int i = 0; i < n - 1; ++i) {
        printf("%.2lf ", data[i]);
    }

    printf("%.2lf", data[n - 1]);
}
