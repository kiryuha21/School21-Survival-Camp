#ifndef SRC_DYNAMICS_H_
#define SRC_DYNAMICS_H_

typedef struct list {
    char* lexem;
    struct list* next;
} list;

list* list_init(char* lexem);
list* add_element(list* elem, char* lexem);
list* list_push(char* lexem, list* tail);
void list_destroy(list* root);
void extended_destroy(list* root);
void handle_push(list** head, list** current, char* lexem);

typedef struct stack {
    char* lexem;
    struct stack* next;
} stack;

stack* stack_push(stack* head, char* lexem);
stack* pop(stack* head);

typedef struct double_stack {
    double num;
    struct double_stack* next;
} double_stack;

double_stack* double_stack_push(double_stack* head, double num);
double_stack* double_stack_pop(double_stack* head);
void destroy_double_stack(double_stack* head);

#endif  // SRC_DYNAMICS_H_
