#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

void test_bstree_create_node();

int main() {
    test_bstree_create_node();
    return 0;
}

void test_bstree_create_node() {
    int number = 10;
    t_btree* tree = bstree_create_node(number);
    printf("IN : %d\n", number);
    printf("OUT : %d %p %p\n", tree->item, tree->left, tree->right);
    printf("RESULT : %s\n\n", tree->item == number &&
                              tree->left == NULL &&
                              tree->right == NULL ? "SUCCESS" : "FAIL");
    free(tree);

    number = -10;
    tree = bstree_create_node(number);
    printf("IN : %d\n", number);
    printf("OUT : %d %p %p\n", tree->item, tree->left, tree->right);
    printf("RESULT : %s", tree->item == number &&
                          tree->left == NULL &&
                          tree->right == NULL ? "SUCCESS" : "FAIL");
    free(tree);
}
