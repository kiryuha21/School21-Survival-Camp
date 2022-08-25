#include <stdlib.h>
#include <string.h>

#include "dynamics.h"

list* list_init(char* lexem) {
    list* head = NULL;

    head = (list*) calloc(1, sizeof(list));
    if (head != NULL) {
        head->lexem = lexem;
        head->next = NULL;
    }

    return head;
}

list* add_element(struct list* elem, char* lexem) {
    list* temp = elem->next;
    elem->next = (list*) calloc(1, sizeof(list));
    struct list* return_value = NULL;
    if (elem->next != NULL) {
        elem->next->next = temp;
        elem->next->lexem = lexem;
        return_value = elem->next;
    } else {
        elem->next = temp;
    }
    return return_value;
}

void handle_push(list** head, list** current, char* lexem) {
    *current = list_push(lexem, *current);
    if (*head == NULL) {
        *head = *current;
    }
}

list* list_push(char* lexem, list* tail) {
    list* return_val = NULL;
    if (tail == NULL) {
        return_val = list_init(lexem);
    } else {
        return_val = add_element(tail, lexem);
    }
    return return_val;
}

void list_destroy(list* root) {
    while (root != NULL) {
        list* temp = root;
        root = root->next;
        free(temp);
    }
}

void extended_destroy(list* root) {
    while (root != NULL) {
        list* temp = root;
        root = root->next;
        free(temp->lexem);
        free(temp);
    }
}

stack* stack_push(struct stack* head, char* lexem) {
    stack* temp = (stack*) calloc(1, sizeof(stack));
    if (temp != NULL) {
        temp->lexem = lexem;
        temp->next = head;
    } else {
        temp = head;
    }
    return temp;
}

stack* pop(stack* head) {
    stack* temp = head;
    head = head->next;
    free(temp);
    return head;
}

double_stack* double_stack_push(double_stack* head, double num) {
    double_stack* temp = (double_stack*) calloc(1, sizeof(double_stack));
    if (temp != NULL) {
        temp->num = num;
        temp->next = head;
    } else {
        temp = head;
    }
    return temp;
}

double_stack* double_stack_pop(double_stack* head) {
    double_stack* temp = head;
    head = head->next;
    free(temp);
    return head;
}

void destroy_double_stack(double_stack* head) {
    while (head != NULL) {
        double_stack* temp = head;
        head = head->next;
        free(temp);
    }
}

