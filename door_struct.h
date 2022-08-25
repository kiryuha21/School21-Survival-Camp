#ifndef SRC_DOOR_STRUCT_H_
#define SRC_DOOR_STRUCT_H_

struct door {
    int id;
    int status;
};

void initialize_doors(struct door* doors);
void sort_doors(struct door* doors);
void set_status(struct door* doors);
void swap(struct door* first, struct door* second);
void print_doors(struct door* doors);

#endif  // SRC_DOOR_STRUCT_H_
