#include <stdlib.h>

#include "stack.h"

struct stack* init(int* arr) {
    struct stack* head = NULL;
    head = push(head, *arr);
    return head;
}

struct stack* push(struct stack* head, int num) {
    struct stack* temp = (struct stack*) calloc(1, sizeof(struct stack));
    if (temp != NULL) {
        temp->number = num;
        temp->next = head;
    } else {
        temp = head;
    }
    return temp;
}

struct stack* pop(struct stack* head) {
    struct stack* temp = head;
    head = head->next;
    free(temp);
    return head;
}

void destroy(struct stack* head) {
    while (head != NULL) {
        struct stack* temp = head;
        head = head->next;
        free(temp);
    }
}
