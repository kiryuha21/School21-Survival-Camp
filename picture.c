//
// Copyright 2022 lyradanu
//

#include <stdio.h>
#include <stdlib.h>

#define ERR -1

#define N 15
#define M 13

void transform(const int *buf, int **matr, int row, int col, int num, int is_row);
int make_picture(int **picture, int n, int m);
void reset_picture(int **picture, int n, int m);
void print_picture(int** picture, int n, int m);
int init_picture(int** picture, int n, int m);

int main() {
    int *picture[N];
    int return_code = make_picture(picture, N, M);
    if (return_code == 0) {
        print_picture(picture, N, M);
        for (int i = 0; i < N; ++i) {
            free(picture[i]);
        }
    }
    return 0;
}

int make_picture(int **picture, int n, int m) {
    int return_code = init_picture(picture, n, m);
    if (return_code == 0) {
        int frame_w[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
        int frame_h[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
        int tree_trunk[] = { 7, 7, 7, 7 };
        int tree_foliage[] = { 3, 3, 3, 3 };
        int sun_data[6][5] = { { 0, 6, 6, 6, 6 },
                              { 0, 0, 6, 6, 6 },
                              { 0, 0, 6, 6, 6 },
                              { 0, 6, 0, 0, 6 },
                              { 0, 0, 0, 0, 0 },
                              { 0, 0, 0, 0, 0 } };

        reset_picture(picture, n, m);

        // tree
        transform(tree_trunk, picture, 10, 2, 4, 1);
        transform(tree_trunk, picture, 6, 4, 4, 0);
        transform(tree_trunk, picture, 6, 3, 4, 0);
        transform(tree_foliage, picture, 2, 3, 4, 0);
        transform(tree_foliage, picture, 2, 4, 4, 0);
        transform(tree_foliage, picture, 3, 2, 4, 1);
        transform(tree_foliage, picture, 4, 2, 4, 1);

        // frames
        transform(frame_w, picture, 0, 0, M, 1);
        transform(frame_w, picture, N - 1, 0, M, 1);
        transform(frame_w, picture, N / 2, 0, M, 1);
        transform(frame_h, picture, 0, 0, N, 0);
        transform(frame_h, picture, 0, M - 1, N, 0);
        transform(frame_h, picture, 0, M / 2, N, 0);

        // sun
        for (int i = 0; i < 6; ++i) {
            transform(sun_data[i], picture, 1 + i, 7, 5, 1);
        }
    }
    return return_code;
}

int init_picture(int** picture, int n, int m) {
    int return_code = 0;
    int cycle_end = 0;
    for (int i = 0; i < n && !cycle_end; ++i) {
        picture[i] = (int*)(calloc(m, sizeof(int)));
        if (picture[i] == NULL) {
            return_code = ERR;
            cycle_end = 1;
            for (int j = i; j >= 0; --j) {
                free(picture[j]);
            }
        }
    }
    return return_code;
}

void print_picture(int** picture, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m - 1; ++j) {
            printf("%d ", picture[i][j]);
        }
        printf("%d\n", picture[i][m - 1]);
    }
}

void reset_picture(int **picture, int n, int m) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            picture[i][j] = 0;
        }
    }
}

void transform(const int *buf, int **matr, int row, int col, int num, int is_row) {
    if (is_row) {
        for (int i = 0; i < num; ++i) {
            matr[row][col + i] = buf[i];
        }
    } else {
        for (int i = 0; i < num; ++i) {
            matr[row + i][col] = buf[i];
        }
    }
}
