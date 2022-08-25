#ifndef SRC_SHARED_H_
#define SRC_SHARED_H_

#define MODULES "../materials/master_modules.db"
#define LEVELS "../materials/master_levels.db"
#define EVENTS "../materials/master_status_events.db"

#define MODULES_INDEX "../materials/modules_index.db"
#define LEVELS_INDEX "../materials/levels_index.db"
#define EVENTS_INDEX "../materials/events_index.db"

typedef struct db_index {
    int id;
    int ind;
} db_index;

int get_position(int id, char* filename);
//  void ouput_index(char* filename);
db_index read_record_from_index_file(FILE *pfile, int index);
int get_records_count_in_index_file(FILE *pfile);
void sort_index_file(FILE* file);
void write_index_in_file(FILE* file, db_index* index, int ind);
int choose_and_open(FILE** file, char** filename, char* mode, int* option);
void choose_db_message();
int read_option(int* option);

#endif  // SRC_SHARED_H_
