#ifndef SRC_MODULES_H_
#define SRC_MODULES_H_

typedef struct module {
    int id;
    char name[30];
    int level_id;
    int cell_id;
    int deleted;
} module;

int create_module_index();
int delete(FILE* file, int single);
int input_module(module** input);
void modules_insert_no_input(FILE* file, module* to_update, const int* ids, int ids_len);
int modules_insert(FILE* file, char* filename);
int* handle_modules_output(FILE* file, int with_deleted);
void output_modules_file(FILE* file, int count, int with_deleted);
module read_record_from_modules_file(FILE *pfile, int index);
int get_records_count_in_modules_file(FILE *pfile);

#endif  // SRC_MODULES_H_
