#include <time.h>
#include <stdio.h>

#include "list.h"

void test_add_door(struct node* head);
struct node* test_remove_door(struct node* head);

int main() {
    struct door start_door = {1, 1};
    struct node* head = init(&start_door);

    test_add_door(head);
    head = test_remove_door(head);

    destroy(head);

    return 0;
}

void test_add_door(struct node* head) {
    struct door test1 = {5, 0};
    printf("IN: door - {id: %d, status:%d}\n", test1.id, test1.status);
    add_door(head, &test1);
    struct node* res = find_door(5, head);
    printf("OUT: node - {door_data: {id: %d, status:%d}}\n", res->door_data.id, res->door_data.status);
    printf("RESULT - %s\n\n", test1.id == res->door_data.id &&
                              test1.status == res->door_data.status ? "SUCCESS" : "FAIL");

    struct door test2 = {6, 1};
    printf("IN: door - {id: %d, status:%d}\n", test2.id, test2.status);
    add_door(head->next, &test2);
    res = find_door(6, head);
    printf("OUT: node - {door_data: {id: %d, status:%d}}\n", res->door_data.id, res->door_data.status);
    printf("RESULT - %s\n\n", test2.id == res->door_data.id &&
                              test2.status == res->door_data.status ? "SUCCESS" : "FAIL");

    struct door test3 = {7, 1};
    printf("IN: door - {id: %d, status:%d}\n", test3.id, test3.status);
    add_door(head->next, &test3);
    res = find_door(7, head);
    printf("OUT: node - {door_data: {id: %d, status:%d}}\n", res->door_data.id, res->door_data.status);
    printf("RESULT - %s\n\n", test3.id == res->door_data.id &&
                              test3.status == res->door_data.status ? "SUCCESS" : "FAIL");
}

struct node* test_remove_door(struct node* head) {
    struct node* target = find_door(5, head);
    printf("IN: door - {id: %d, status:%d}\n", target->door_data.id, target->door_data.status);
    head = remove_door(target, head);
    printf("OUT:\n");
    printf("RESULT - %s\n\n", find_door(5, head) == NULL ? "SUCCESS" : "FAIL");

    target = find_door(7, head);
    printf("IN: door - {id: %d, status:%d}\n", target->door_data.id, target->door_data.status);
    head = remove_door(target, head);
    printf("OUT:\n");
    printf("RESULT - %s\n\n", find_door(7, head) == NULL ? "SUCCESS" : "FAIL");

    target = find_door(6, head);
    printf("IN: door - {id: %d, status:%d}\n", target->door_data.id, target->door_data.status);
    head = remove_door(target, head);
    printf("OUT:\n");
    printf("RESULT - %s\n\n", find_door(3, head) == NULL ? "SUCCESS" : "FAIL");

    int res_id = head->door_data.id;
    printf("IN: door - {id: %d, status:%d}\n", head->door_data.id, head->door_data.status);
    head = remove_door(head, head);
    printf("OUT:\n");
    printf("RESULT - %s\n\n", find_door(res_id, head) == NULL ? "SUCCESS" : "FAIL");

    return head;
}
