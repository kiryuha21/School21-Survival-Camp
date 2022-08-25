#include <stdlib.h>

#include "list.h"

struct node* init(const struct door* door) {
    struct node* head = NULL;

    head = (struct node*) calloc(1, sizeof(struct node));
    if (head != NULL) {
        head->door_data = *door;
        head->next = NULL;
    }

    return head;
}

struct node* add_door(struct node* elem, const struct door* door) {
    struct node* temp = elem->next;
    elem->next = (struct node*) calloc(1, sizeof(struct node));
    struct node* return_value = NULL;
    if (elem->next != NULL) {
        elem->next->next = temp;
        elem->next->door_data = *door;
        return_value = elem->next;
    } else {
        elem->next = temp;
    }
    return return_value;
}

struct node* find_door(int door_id, struct node* root) {
    struct node* curr = NULL;
    for (curr = root; curr != NULL && curr->door_data.id != door_id; curr = curr->next) { }
    return curr;
}

struct node* remove_door(struct node* elem, struct node* root) {
    struct node* curr = NULL;
    if (elem != NULL) {
        if (elem == root) {
            struct node* temp = root->next;
            free(root);
            root = temp;
        } else {
            for (curr = root; curr != NULL && curr->next != elem; curr = curr->next) {}
            if (curr != NULL) {
                struct node *temp = curr->next;
                curr->next = curr->next->next;
                free(temp);
            }
        }
    }
    return root;
}

void destroy(struct node* root) {
    while (root != NULL) {
        struct node* temp = root;
        root = root->next;
        free(temp);
    }
}
