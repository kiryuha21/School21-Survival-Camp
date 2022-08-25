#include "dynamics.h"
#include "main_utils.h"

int find_closest(double y) {
    int min_ind = 0;
    if (y > 1 + EPS || y < -1 - EPS || isnan(y)) {
        min_ind = -1;
    } else {
        int count = 1;
        double min = fabs(-1 - y);
        for (double j = -1 + STEP_Y; count < 25; j += STEP_Y, ++count) {
            double diff = fabs(j - y);
            if (diff < min) {
                min = diff;
                min_ind = count;
            }
        }
    }
    return min_ind;
}

void draw_graph(double (*func)(double, list*, int*), list* parsed_polish, int* err) {
    char result[HEIGHT][WIDTH];
    int count = 0;
    for (double i = 0; *err == 0 && count < WIDTH; i += STEP_X, ++count) {
        double y = func(i, parsed_polish, err);
        if (*err == 0) {
            int ind = find_closest(y);
            for (int j = 0; j < HEIGHT; ++j) {
                result[j][count] = j == ind ? '*' : '.';
            }
        }
    }

    if (*err == 0) {
        for (int i = 0; i < HEIGHT; ++i) {
            for (int j = 0; j < WIDTH; ++j) {
                printf("%c", result[i][j]);
            }
            printf("\n");
        }
    }
}

