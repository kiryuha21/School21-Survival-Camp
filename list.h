#ifndef SRC_LIST_H_
#define SRC_LIST_H_

#include "door_struct.h"

#define MAX_ID_SEED 10000

struct node {
    struct door door_data;
    struct node* next;
};

struct node* init(const struct door* door);
struct node* add_door(struct node* elem, const struct door* door);
struct node* find_door(int door_id, struct node* root);
struct node* remove_door(struct node* elem, struct node* root);
void destroy(struct node* root);

#endif  // SRC_LIST_H_
