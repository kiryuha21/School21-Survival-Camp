#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "modules.h"
#include "shared.h"

void write_module_in_file(FILE *pfile, const module *record_to_write, int index) {
    int offset = index * sizeof(module);
    fseek(pfile, offset, SEEK_SET);
    fwrite(record_to_write, sizeof(module), 1, pfile);
    fflush(pfile);
    rewind(pfile);
}

int is_module_id_duplicates(FILE* file, char* filename, int id) {
    int return_value = 0;

    close_file(&file);
    file = fopen(filename, "rb");
    if (file != NULL) {
        int size = get_records_count_in_modules_file(file);
        for (int i = 0; return_value == 0 && i < size; ++i) {
            module temp = read_record_from_modules_file(file, i);
            if (temp.id == id) {
                return_value = 1;
            }
        }
    } else {
        return_value = ERR;
    }

    return return_value;
}

void append_keyword(char* name) {
    size_t len = strlen(name);
    if (len < 23) {
        name[len] = ' ';
        name[len + 1] = 'm';
        name[len + 2] = 'o';
        name[len + 3] = 'd';
        name[len + 4] = 'u';
        name[len + 5] = 'l';
        name[len + 6] = 'e';
        name[len + 7] = '\0';
    }
}

int input_module(module** input) {
    int return_value = 0;

    *input = (module*) calloc(1, sizeof(module));
    if (*input != NULL) {
        printf("Enter module in format [id] [name] [level_id] [cell_id] [deleted]:\n");
        if (scanf("%d%29s%d%d%d", &((*input)->id), (*input)->name, &((*input)->level_id),
                                &((*input)->cell_id), &((*input)->deleted)) != 5 || (*input)->id < 0) {
            return_value = ERR;
            flush_stdin();
            free(*input);
            *input = NULL;
        } else {
            append_keyword((*input)->name);
        }
    } else {
        return_value = ERR;
    }

    return return_value;
}

int delete(FILE* file, int single) {
    int return_value = 0;

    int arr_size;
    int *number = empty_or_positive_array(&arr_size);
    if (single) {
        arr_size = 1;
    }
    if (number != NULL) {
        for (int j = 0; j < arr_size; ++j) {
            int pos = get_position(number[j], MODULES_INDEX);
            if (pos != -1) {
                module temp = read_record_from_modules_file(file, pos);
                temp.deleted = 1;
                write_module_in_file(file, &temp, pos);
            }
        }
        close_file(&file);
    } else {
        return_value = 1;
    }
    clear_ints(&number);

    return return_value;
}

int create_module_index() {
    int return_code = 0;

    FILE* orig = fopen(MODULES, "rb");
    if (orig != NULL) {
        FILE* file = fopen(MODULES_INDEX, "wb");
        int size = get_records_count_in_modules_file(orig);
        for (int i = 0; i < size; ++i) {
            module temp_module = read_record_from_modules_file(orig, i);
            db_index temp = {temp_module.id, i};
            write_index_in_file(file, &temp, i);
        }
        fclose(orig);
        fclose(file);
        file = fopen(MODULES_INDEX, "rb+");
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

void modules_insert_no_input(FILE* file, module* to_update, const int* ids, int ids_len) {
    for (int j = 0; j < ids_len; ++j) {
        int pos = get_position(ids[j], MODULES_INDEX);
        if (pos != -1) {
            write_module_in_file(file, to_update, pos);
        }
    }
    close_file(&file);
}

int modules_insert(FILE* file, char* filename) {
    int return_value = 0;

    module* to_insert = NULL;
    if (input_module(&to_insert) == 0) {
        if (!is_module_id_duplicates(file, filename, to_insert->id)) {
            int size = get_records_count_in_modules_file(file);
            close_file(&file);
            file = fopen(filename, "ab");
            if (file != NULL) {
                write_module_in_file(file, to_insert, size);
                FILE* index_file = fopen(MODULES_INDEX, "rb+");
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

int* handle_modules_output(FILE* file, int with_deleted) {
    printf("> Insert the number of records or leave empty to output all of them: ");

    int size;
    int* number = empty_or_positive_array(&size);
    if (number != NULL) {
        output_modules_file(file, number[0], with_deleted);
    }
    return number;
}

void output_modules_file(FILE* file, int count, int with_deleted) {
    int size = get_records_count_in_modules_file(file);
    if (count > size || count == -1) {
        count = size;
    }
    for (int i = 0; i < count; ++i) {
        module temp = read_record_from_modules_file(file, i);
        if ((!with_deleted && temp.deleted == 0) || with_deleted) {
            printf("%d %s %d %d %d\n", temp.id, temp.name, temp.level_id, temp.cell_id, temp.deleted);
        }
    }
}

module read_record_from_modules_file(FILE *pfile, int index) {
    int offset = index * sizeof(module);
    fseek(pfile, offset, SEEK_SET);

    module record;
    fread(&record, sizeof(module), 1, pfile);

    // For safety reasons, we return the file position pointer to the beginning of the file.
    rewind(pfile);

    // Return read record
    return record;
}

int get_records_count_in_modules_file(FILE *pfile) {
    return get_file_size_in_bytes(pfile) / sizeof(module);
}
