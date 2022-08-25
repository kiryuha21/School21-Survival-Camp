#include "data_stat.h"

double max(const double *data, int n) {
    double res = data[0];
    for (int i = 1; i < n; ++i) {
        if (data[i] > res) {
            res = data[i];
        }
    }
    return res;
}

double min(const double *data, int n) {
    double res = data[0];
    for (int i = 1; i < n; ++i) {
        if (data[i] < res) {
            res = data[i];
        }
    }
    return res;
}

double mean(const double *data, int n) {
    double sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += data[i];
    }
    return sum / n;
}

double variance(double *data, int n) {
    double sum = 0;
    double mid = mean(data, n);

    for (int i = 0; i < n; ++i) {
        sum += (data[i] - mid) * (data[i] - mid);
    }

    return sum / n;
}
