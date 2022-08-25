#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#define ERR -1

char* get_string();
void clear_string(char** line);
void clear_ints(int** arr);
void flush_stdin();
int get_file_size_in_bytes(FILE *pfile);
int* empty_or_positive_array(int* size);
void close_file(FILE** file);

#endif  // SRC_UTILS_H_
