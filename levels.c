#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "levels.h"
#include "shared.h"

void write_level_in_file(FILE *pfile, const level *record_to_write, int index) {
    int offset = index * sizeof(level);
    fseek(pfile, offset, SEEK_SET);
    fwrite(record_to_write, sizeof(level), 1, pfile);
    fflush(pfile);
    rewind(pfile);
}

int* handle_levels_output(FILE* file) {
    printf("> Insert the number of records or leave empty to output all of them: ");

    int size;
    int* number = empty_or_positive_array(&size);
    if (number != NULL) {
        output_levels_file(file, number[0]);
    }
    return number;
}

int is_level_id_duplicates(FILE* file, char* filename, int id) {
    int return_value = 0;

    close_file(&file);
    file = fopen(filename, "rb");
    if (file != NULL) {
        int size = get_records_count_in_levels_file(file);
        for (int i = 0; return_value == 0 && i < size; ++i) {
            level temp = read_record_from_levels_file(file, i);
            if (temp.id == id) {
                return_value = 1;
            }
        }
    } else {
        return_value = ERR;
    }

    return return_value;
}

int input_level(level** input) {
    int return_value = 0;

    *input = (level*) calloc(1, sizeof(level));
    if (*input != NULL) {
        printf("Enter level in format [id] [cells_count] [security_flag]:\n");
        if (scanf("%d%d%d", &((*input)->id), &((*input)->cells_count), &((*input)->security_flag)) != 3 ||
                            (*input)->id < 0) {
            return_value = ERR;
            flush_stdin();
            free(*input);
            *input = NULL;
        }
    } else {
        return_value = ERR;
    }

    return return_value;
}

int create_level_index() {
    int return_code = 0;

    FILE* orig = fopen(LEVELS, "rb");
    if (orig != NULL) {
        FILE* file = fopen(LEVELS_INDEX, "wb");
        int size = get_records_count_in_levels_file(orig);
        for (int i = 0; i < size; ++i) {
            level temp_module = read_record_from_levels_file(orig, i);
            db_index temp = {temp_module.id, i};
            write_index_in_file(file, &temp, i);
        }
        fclose(orig);
        fclose(file);
        file = fopen(LEVELS_INDEX, "rb+");
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

void levels_insert_no_input(FILE* file, level* to_update, const int* ids, int ids_len) {
    for (int j = 0; j < ids_len; ++j) {
        int pos = get_position(ids[j], LEVELS_INDEX);
        if (pos != -1) {
            write_level_in_file(file, to_update, pos);
        }
    }
    close_file(&file);
}

int levels_insert(FILE* file, char* filename) {
    int return_value = 0;

    level* to_insert = NULL;
    if (input_level(&to_insert) == 0) {
        if (!is_level_id_duplicates(file, filename, to_insert->id)) {
            int size = get_records_count_in_levels_file(file);
            close_file(&file);
            file = fopen(filename, "ab");
            if (file != NULL) {
                write_level_in_file(file, to_insert, size);
                FILE* index_file = fopen(LEVELS_INDEX, "rb+");
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

void output_levels_file(FILE* file, int count) {
    int size = get_records_count_in_levels_file(file);
    if (count > size || count == -1) {
        count = size;
    }
    for (int i = 0; i < count; ++i) {
        level temp = read_record_from_levels_file(file, i);
        printf("%d %d %d\n", temp.id, temp.cells_count, temp.security_flag);
    }
}

level read_record_from_levels_file(FILE *pfile, int index) {
    int offset = index * sizeof(level);
    fseek(pfile, offset, SEEK_SET);

    level record;
    fread(&record, sizeof(level), 1, pfile);

    // For safety reasons, we return the file position pointer to the beginning of the file.
    rewind(pfile);

    // Return read record
    return record;
}

int find_level_index(FILE* file, int id) {
    int result = -1;
    int size = get_records_count_in_levels_file(file);
    int found = 0;
    for (int i = 0; !found && i < size; ++i) {
        if (read_record_from_levels_file(file, i).id == id) {
            result = i;
            found = 1;
        }
    }
    return result;
}

int get_records_count_in_levels_file(FILE *pfile) {
    return get_file_size_in_bytes(pfile) / sizeof(level);
}
