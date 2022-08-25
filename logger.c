#include <stdio.h>
#include <time.h>

#include "logger.h"

FILE* log_init(char *filename) {
    FILE* log = NULL;
    log = fopen(filename, "w");
    return log;
}

char* string_level(log_level level) {
    char* result;

    if (level == debug) {
        result = "DEBUG";
    } else if (level == trace) {
        result = "TRACE";
    } else if (level == info) {
        result = "INFO";
    } else if (level == warning) {
        result = "WARNING";
    } else {
        result = "ERROR";
    }

    return result;
}

int logcat(FILE* log_file, char *message, log_level level) {
    time_t current_time;
    struct tm * time_info;
    char time_string[9];  // space for "HH:MM:SS\0"

    time(&current_time);
    time_info = localtime(&current_time);

    strftime(time_string, sizeof(time_string), "%H:%M:%S", time_info);
    fprintf(log_file, "[%s] %s %s\n", string_level(level), time_string, message);

    return 0;
}

int log_close(FILE* log_file) {
    return fclose(log_file);
}
