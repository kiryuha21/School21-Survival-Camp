#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dynamics.h"
#include "main_utils.h"
#include "polish_notation.h"
#include "parse.h"

int main() {
    char* line = NULL;
    size_t size;
    int err = 0;

    getline(&line, &size, stdin);
    line[strlen(line) - 1] = '\0';
    list* line_list = parse_line(line, &err);
    if (err == 0) {
        list* parsed = parse_to_polish(line_list, &err);
        if (err == 0) {
            draw_graph(apply_polish, parsed, &err);
            if (err != 0) {
                puts("Wrong function format!");
            }
        } else {
            puts("error during polish notation building");
        }
        list_destroy(parsed);
    } else {
        puts("error during line parsing");
    }
    extended_destroy(line_list);
    free(line);

    return 0;
}
