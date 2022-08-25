#include <stdio.h>

#include "bst.h"

void test_bstree_insert_node_1(t_btree* tree);
void test_bstree_insert_node_2(t_btree* tree);

int main() {
    t_btree* tree = bstree_create_node(5);
    test_bstree_insert_node_1(tree);
    destroy(tree);

    tree = bstree_create_node(35);
    test_bstree_insert_node_2(tree);
    destroy(tree);

    return 0;
}

void test_bstree_insert_node_1(t_btree* tree) {
    int number = 10;
    bstree_insert(tree, number, default_compare);
    printf("IN : %d\n", number);
    printf("OUT : %d\n", tree->right->item);
    printf("Infix ouput - ");
    bstree_apply_infix(tree, simple_print);
    printf("\nRESULT : %s\n\n", tree->right->item == number ? "SUCCESS" : "FAIL");

    number = 2;
    bstree_insert(tree, number, default_compare);
    printf("IN : %d\n", number);
    printf("OUT : %d\n", tree->left->item);
    printf("Infix ouput - ");
    bstree_apply_infix(tree, simple_print);
    printf("\nRESULT : %s\n\n", tree->left->item == number ? "SUCCESS" : "FAIL");

    number = 11;
    bstree_insert(tree, number, default_compare);
    printf("IN : %d\n", number);
    printf("OUT : %d\n", tree->right->right->item);
    printf("Infix ouput - ");
    bstree_apply_infix(tree, simple_print);
    printf("\nRESULT : %s\n\n", tree->right->right->item == number ? "SUCCESS" : "FAIL");

    number = 8;
    bstree_insert(tree, number, default_compare);
    printf("IN : %d\n", number);
    printf("OUT : %d\n", tree->right->left->item);
    printf("Infix ouput - ");
    bstree_apply_infix(tree, simple_print);
    printf("\nRESULT : %s\n\n", tree->right->left->item == number ? "SUCCESS" : "FAIL");
}

void test_bstree_insert_node_2(t_btree* tree) {
    int number = 9;
    bstree_insert(tree, number, digits_sum_compare);
    printf("IN : %d\n", number);
    printf("OUT : %d\n", tree->right->item);
    printf("Infix ouput - ");
    bstree_apply_infix(tree, simple_print);
    printf("\nRESULT : %s\n\n", tree->right->item == number ? "SUCCESS" : "FAIL");

    number = 40;
    bstree_insert(tree, number, digits_sum_compare);
    printf("IN : %d\n", number);
    printf("OUT : %d\n", tree->left->item);
    printf("Infix ouput - ");
    bstree_apply_infix(tree, simple_print);
    printf("\nRESULT : %s\n\n", tree->left->item == number ? "SUCCESS" : "FAIL");
}
