#include <stdio.h>
#include <time.h>

#include "print_module.h"

char print_char(char ch) {
    return putchar(ch);
}

void print_log(char(*print)(char), const char* message) {
    time_t current_time;
    struct tm* time_info;
    char time_string[9];  // space for "HH:MM:SS\0"

    time(&current_time);
    time_info = localtime(&current_time);

    strftime(time_string, sizeof(time_string), "%H:%M:%S", time_info);

    printf("%s %s ", Log_prefix, time_string);
    for (const char* ch = message; *ch != '\0'; ++ch) {
        print(*ch);
    }
}
