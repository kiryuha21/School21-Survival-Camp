#include <stdio.h>
#include <stdlib.h>

#include "decision.h"
#include "data_io.h"

int main() {
    double *data = NULL;
    int n;

    data = input(&n);
    if (data != NULL) {
        if (make_decision(data, n)) {
            printf("YES");
        } else {
            printf("NO");
        }
        free(data);
    } else {
        printf("n/a");
    }
    return 0;
}
