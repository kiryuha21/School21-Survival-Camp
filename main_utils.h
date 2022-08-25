#ifndef SRC_MAIN_UTILS_H_
#define SRC_MAIN_UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 80
#define HEIGHT 25

#define STEP_X 4 * M_PI / 79
#define STEP_Y 2.0 / 24
#define EPS STEP_Y / 2

int find_closest(double y);
void draw_graph(double (*func)(double, list*, int*), list* parsed_polish, int* err);

#endif  // SRC_MAIN_UTILS_H_

