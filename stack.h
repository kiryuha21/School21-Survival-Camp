#ifndef SRC_STACK_H_
#define SRC_STACK_H_

struct stack {
    int number;
    struct stack* next;
};

struct stack* init(int* arr);
struct stack* push(struct stack* head, int num);
struct stack* pop(struct stack* head);
void destroy(struct stack* head);

#endif  // SRC_STACK_H_
