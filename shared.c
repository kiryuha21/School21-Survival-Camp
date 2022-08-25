#include <stdio.h>
#include <string.h>

#include "shared.h"
#include "utils.h"

int get_position(int id, char* filename) {
    int res = -1;
    FILE* indexes = fopen(filename, "rb");
    if (indexes != NULL) {
        int filesize = get_records_count_in_index_file(indexes);
        int l = 0, r = filesize;
        while (l <= r && res == -1) {
            db_index new = read_record_from_index_file(indexes, l + (r - l) / 2);
            if (new.id > id) {
                r = r - (r - l) / 2 - 1;
            } else if (new.id < id) {
                l = l + (r - l) / 2 + 1;
            } else {
                res = new.ind;
            }
        }
        fclose(indexes);
    }
    return res;
}

void write_index_in_file(FILE *file, db_index *index, int ind) {
    int offset = ind * sizeof(db_index);
    fseek(file, offset, SEEK_SET);
    fwrite(index, sizeof(db_index), 1, file);
    fflush(file);
    rewind(file);
}

db_index read_record_from_index_file(FILE *pfile, int index) {
    int offset = index * sizeof(db_index);
    fseek(pfile, offset, SEEK_SET);

    db_index record;
    fread(&record, sizeof(db_index), 1, pfile);

    // For safety reasons, we return the file position pointer to the beginning of the file.
    rewind(pfile);

    // Return read record
    return record;
}

int get_records_count_in_index_file(FILE *pfile) {
    return get_file_size_in_bytes(pfile) / sizeof(db_index);
}

void sort_index_file(FILE* file) {
    int size = get_records_count_in_index_file(file);
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            db_index first = read_record_from_index_file(file, j);
            db_index second = read_record_from_index_file(file, j + 1);
            if (first.id > second.id) {
                write_index_in_file(file, &first, j + 1);
                write_index_in_file(file, &second, j);
            }
        }
    }
}

//  void ouput_index(char* filename) {
//      FILE* file = fopen(filename, "rb");
//      int size = get_records_count_in_index_file(file);
//      for (int i = 0; i < size; ++i) {
//          db_index temp = read_record_from_index_file(file, i);
//          printf("id - %d, pos - %d\n", temp.id, temp.ind);
//      }
//  }

int choose_and_open(FILE** file, char** filename, char* mode, int* option) {
    int return_value = 0;
    choose_db_message();
    if (read_option(option) == 0) {
        if (*option == 1) {
            *filename = MODULES;
        } else if (*option == 2) {
            *filename = LEVELS;
        } else {  // option == 3
            *filename = EVENTS;
        }
        close_file(file);
        *file = fopen(*filename, mode);
        if (*file == NULL) {
            return_value = ERR;
        }
    } else {
        return_value = ERR;
    }
    return return_value;
}

void choose_db_message() {
    printf("Please choose a table:\n\t1. Modules\n\t2. Levels\n\t3. Status events\n> ");
}

int read_option(int* option) {
    char sym;
    int return_value = 0;
    int count = scanf("%d%c", option, &sym);
    if (count != 2 || sym != '\n') {
        flush_stdin();
        return_value = ERR;
    } else if (*option != 1 && *option != 2 && *option != 3) {
        return_value = ERR;
    }
    return return_value;
}
