#ifndef SRC_MODULES_DB_H_
#define SRC_MODULES_DB_H_

void operations_list_message();
int read_main_option(int* option);
void handle_error();
int handle_select(FILE* file, int option);
int handle_insert(FILE* file, char* filename, int option);
int handle_update(FILE* file, int option);
int option_5(FILE* file);
int option_7(FILE* file);
int option_8(FILE* file);
int option_9(FILE* file);
int quest_completed(FILE* file);

#endif  // SRC_MODULES_DB_H_
