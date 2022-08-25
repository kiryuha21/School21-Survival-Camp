#ifndef SRC_STATUS_EVENTS_H_
#define SRC_STATUS_EVENTS_H_

typedef struct status_event {
    int id;
    int module_id;
    int new_status;
    char status_change_date[11];
    char status_change_time[9];
} status_event;

int create_events_index();
void write_time(char* arr);
void write_date(char* arr);
status_event* new_event(int id, int module_id, int new_status);
void write_event_in_file(FILE *pfile, const status_event *record_to_write, int index);
int input_event(status_event ** input);
void events_insert_no_input(FILE* file, status_event* to_update, const int* ids, int ids_len);
int events_insert(FILE* file, char* filename);
int* handle_events_output(FILE* file);
void output_events_file(FILE* file, int count);
status_event read_record_from_events_file(FILE *pfile, int index);
int get_records_count_in_events_file(FILE *pfile);

#endif  // SRC_STATUS_EVENTS_H_
