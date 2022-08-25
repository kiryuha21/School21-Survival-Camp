#include <math.h>

#include "data_process.h"
#include "data_stat.h"

int normalization(double *data, int n) {
    int result = 1;
    double max_value = max(data, n);
    double min_value = min(data, n);
    double size = max_value - min_value;

    if (fabs(size) >= EPS) {
        for (int i = 0; i < n; i++) {
            data[i] = data[i] / size - min_value / size;
        }
    } else if (n == 1) {
        data[n] = 1;
    } else {
        result = 0;
    }

    return result;
}

void sort(double* data, int first, int last) {
    if (first < last) {
        int pivot = first;
        int i = first;
        int j = last;
        while (i < j) {
            while (i < last && data[i] <= data[pivot]) {
                ++i;
            }
            while (data[j] > data[pivot]) {
                --j;
            }
            if (i < j) {
                swap(data + i, data + j);
            }
        }
        swap(data + pivot, data + j);
        sort(data, first, j - 1);
        sort(data, j + 1, last);
    }
}

void swap(double* first, double* second) {
    double temp = *first;
    *first = *second;
    *second = temp;
}
