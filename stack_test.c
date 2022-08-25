#include <stdio.h>

#include "stack.h"

struct stack* test_push(struct stack* head);
struct stack* test_pop(struct stack* head);

int main() {
    int arr = 1;
    struct stack* head = init(&arr);

    head = test_push(head);
    head = test_pop(head);

    destroy(head);
    return 0;
}

struct stack* test_push(struct stack* head) {
    int num = 5;
    head = push(head, num);
    printf("IN - %d\n", num);
    printf("OUT - %d\n", head->number);
    printf("RESULT - %s\n\n", head->number == num ? "SUCCESS" : "FAIL");

    num = 6;
    head = push(head, num);
    printf("IN - %d\n", num);
    printf("OUT - %d\n", head->number);
    printf("RESULT - %s\n\n", head->number == num ? "SUCCESS" : "FAIL");

    num = 7;
    head = push(head, num);
    printf("IN - %d\n", num);
    printf("OUT - %d\n", head->number);
    printf("RESULT - %s\n\n", head->number == num ? "SUCCESS" : "FAIL");

    return head;
}

struct stack* test_pop(struct stack* head) {
    printf("IN -\n");
    int res = head->next->number;
    head = pop(head);
    printf("OUT - %d\n", res);
    printf("RESULT - %s\n\n", res == head->number ? "SUCCESS" : "FAIL");

    printf("IN -\n");
    res = head->next->number;
    head = pop(head);
    printf("OUT - %d\n", res);
    printf("RESULT - %s\n\n", res == head->number ? "SUCCESS" : "FAIL");

    printf("IN -\n");
    res = head->next->number;
    head = pop(head);
    printf("OUT - %d\n", res);
    printf("RESULT - %s\n\n", res == head->number ? "SUCCESS" : "FAIL");

    return head;
}
