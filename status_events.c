#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"
#include "status_events.h"
#include "shared.h"

void write_event_in_file(FILE *pfile, const status_event *record_to_write, int index) {
    int offset = index * sizeof(status_event);
    fseek(pfile, offset, SEEK_SET);
    fwrite(record_to_write, sizeof(status_event), 1, pfile);
    fflush(pfile);
    rewind(pfile);
}

status_event* new_event(int id, int module_id, int new_status) {
    status_event* res = (status_event*) calloc(1, sizeof(status_event));
    if (res != NULL) {
        res->id = id;
        res->module_id = module_id;
        res->new_status = new_status;
        write_date(res->status_change_date);
        write_time(res->status_change_time);
    }
    return res;
}

int create_events_index() {
    int return_code = 0;

    FILE* orig = fopen(EVENTS, "rb");
    if (orig != NULL) {
        FILE* file = fopen(EVENTS_INDEX, "wb");
        int size = get_records_count_in_events_file(orig);
        for (int i = 0; i < size; ++i) {
            status_event temp_module = read_record_from_events_file(orig, i);
            db_index temp = {temp_module.id, i};
            write_index_in_file(file, &temp, i);
        }
        fclose(orig);
        fclose(file);
        file = fopen(EVENTS_INDEX, "rb+");
        if (file != NULL) {
            sort_index_file(file);
            fclose(file);
        } else {
            return_code = ERR;
        }
    } else {
        return_code = ERR;
    }

    return return_code;
}

int is_event_id_duplicates(FILE* file, char* filename, int id) {
    int return_value = 0;

    close_file(&file);
    file = fopen(filename, "rb");
    if (file != NULL) {
        int size = get_records_count_in_events_file(file);
        for (int i = 0; return_value == 0 && i < size; ++i) {
            status_event temp = read_record_from_events_file(file, i);
            if (temp.id == id) {
                return_value = 1;
            }
        }
    } else {
        return_value = ERR;
    }

    return return_value;
}

void write_time(char* arr) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    sprintf(arr, "%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);
}

void write_date(char* arr) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    sprintf(arr, "%02d.%02d.%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

int input_event(status_event** input) {
    int return_value = 0;

    *input = (status_event *) calloc(1, sizeof(status_event));
    if (*input != NULL) {
        printf("Enter status event in format [id] [module_id] [new_status]:\n");
        if (scanf("%d%d%d", &((*input)->id), &((*input)->module_id), &((*input)->new_status)) != 3 ||
                            (*input)->id < 0) {
            return_value = ERR;
            flush_stdin();
            free(*input);
            *input = NULL;
        } else {
            write_time((*input)->status_change_time);
            write_date((*input)->status_change_date);
        }
    } else {
        return_value = ERR;
    }

    return return_value;
}

void events_insert_no_input(FILE* file, status_event* to_update, const int* ids, int ids_len) {
    for (int j = 0; j < ids_len; ++j) {
        int pos = get_position(ids[j], EVENTS_INDEX);
        if (pos != -1) {
            write_event_in_file(file, to_update, pos);
        }
    }
    close_file(&file);
}

int events_insert(FILE* file, char* filename) {
    int return_value = 0;

    status_event * to_insert = NULL;
    if (input_event(&to_insert) == 0) {
        if (!is_event_id_duplicates(file, filename, to_insert->id)) {
            int size = get_records_count_in_events_file(file);
            close_file(&file);
            file = fopen(filename, "ab");
            if (file != NULL) {
                write_event_in_file(file, to_insert, size);
                FILE* index_file = fopen(EVENTS_INDEX, "rb+");
                int indexes_size = get_records_count_in_index_file(index_file);
                db_index temp = {to_insert->id, size};
                write_index_in_file(index_file, &temp, indexes_size);
                sort_index_file(index_file);
                fclose(index_file);
            } else {
                return_value = ERR;
            }
            close_file(&file);
        } else {
            return_value = ERR;
        }
        free(to_insert);
    } else {
        return_value = ERR;
    }

    return return_value;
}

int* handle_events_output(FILE* file) {
    printf("> Insert the number of records or leave empty to output all of them: ");

    int size;
    int* number = empty_or_positive_array(&size);
    if (number != NULL) {
        output_events_file(file, number[0]);
    }
    return number;
}

void output_events_file(FILE* file, int count) {
    int size = get_records_count_in_events_file(file);
    if (count > size || count == -1) {
        count = size;
    }
    for (int i = 0; i < count; ++i) {
        status_event temp = read_record_from_events_file(file, i);
        printf("%d %d %d %s %s\n", temp.id, temp.module_id, temp.new_status,
               temp.status_change_date, temp.status_change_time);
    }
}

status_event read_record_from_events_file(FILE *pfile, int index) {
    int offset = index * sizeof(status_event);
    fseek(pfile, offset, SEEK_SET);

    status_event record;
    fread(&record, sizeof(status_event), 1, pfile);

    // For safety reasons, we return the file position pointer to the beginning of the file.
    rewind(pfile);

    // Return read record
    return record;
}

int get_records_count_in_events_file(FILE *pfile) {
    return get_file_size_in_bytes(pfile) / sizeof(status_event);
}
