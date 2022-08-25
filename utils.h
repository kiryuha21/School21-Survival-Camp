#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#define ERR -1

typedef struct state {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int status;
    int code;
} state;

int is_in_interval(int year, int month, int date,
                   int first_year, int first_month, int first_day,
                   int second_year, int second_month, int second_day);
int clear_interval(FILE* file, char* filename,
                   int first_year, int first_month, int first_day,
                   int second_year, int second_month, int second_day);
char* full_path(char* dir, char* name);
char* get_string();
void flush_stdin();
void close_file(FILE** file);
void clear_string(char** line);
void handle_error();
int read_option(int* option);
state input_state(int* err);
struct state read_record_from_file(FILE *pfile, int index);
int get_records_count_in_file(FILE *pfile);
int get_file_size_in_bytes(FILE *pfile);
void output_struct_file(FILE* file);
void sort_binary(FILE* file);
void convert_date(char* datestring, int* year, int* month, int* day);
int first_entry(FILE** file, char* filename, int year, int month, int day);
int compare(state first, state second);
void swap_records_in_file(FILE *pfile, int record_index1, int record_index2);
void write_record_in_file(FILE *pfile, const state *record_to_write, int index);
int is_valid_date(const char* date);
int is_digit(char ch);

#endif  // SRC_UTILS_H_
