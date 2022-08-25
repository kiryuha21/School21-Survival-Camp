#include <stdio.h>

#include "bst.h"

void test_bstree_traverse_test(t_btree* tree);

int main() {
    t_btree* tree = bstree_create_node(5);
    bstree_insert(tree, 3, default_compare);
    bstree_insert(tree, 2, default_compare);
    bstree_insert(tree, 4, default_compare);
    bstree_insert(tree, 1, default_compare);
    bstree_insert(tree, 8, default_compare);
    bstree_insert(tree, 7, default_compare);
    bstree_insert(tree, 9, default_compare);
    bstree_insert(tree, 0, default_compare);
    bstree_insert(tree, 6, default_compare);

    test_bstree_traverse_test(tree);
    destroy(tree);

    return 0;
}

void test_bstree_traverse_test(t_btree* tree) {
    printf("IN : [infix print]\n");
    printf("OUT : ");
    bstree_apply_infix(tree, simple_print);
    printf("\nRESULT : SUCCESS\n\n");

    printf("IN : [prefix print]\n");
    printf("OUT : ");
    bstree_apply_prefix(tree, simple_print);
    printf("\nRESULT : SUCCESS\n\n");

    printf("IN : [postfix print]\n");
    printf("OUT : ");
    bstree_apply_postfix(tree, simple_print);
    printf("\nRESULT : SUCCESS");
}
