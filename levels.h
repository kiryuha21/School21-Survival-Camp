#ifndef SRC_LEVELS_H_
#define SRC_LEVELS_H_

typedef struct level {
    int id;
    int cells_count;
    int security_flag;
} level;

int create_level_index();
int input_level(level** input);
void levels_insert_no_input(FILE* file, level* to_update, const int* ids, int ids_len);
int levels_insert(FILE* file, char* filename);
int* handle_levels_output(FILE* file);
void output_levels_file(FILE* file, int count);
int find_level_index(FILE* file, int id);
level read_record_from_levels_file(FILE *pfile, int index);
int get_records_count_in_levels_file(FILE *pfile);

#endif  // SRC_LEVELS_H_
