#include "bst.h"

#include <stdlib.h>
#include <stdio.h>

t_btree* bstree_create_node(int item) {
    t_btree* tree = NULL;
    tree = (t_btree*) calloc(1, sizeof(t_btree));
    if (tree != NULL) {
        tree->right = NULL;
        tree->left = NULL;
        tree->item = item;
    }
    return tree;
}

void simple_print(int n) {
    printf("%d ", n);
}

int default_compare(int first, int second) {
    return first - second;
}

int digits_sum_compare(int first, int second) {
    int sum1 = 0;
    int sum2 = 0;

    while (first > 0) {
        sum1 += first % 10;
        first /= 10;
    }

    while (second > 0) {
        sum2 += second % 10;
        second /= 10;
    }

    return sum1 - sum2;
}

void bstree_insert(t_btree *root, int item, int (*cmpf)(int, int)) {
    t_btree* temp = root;

    while ((temp->right != NULL && cmpf(temp->item, item) < 0) ||
            (temp->left != NULL && cmpf(temp->item, item) > 0)) {
        if (temp->right != NULL && cmpf(temp->item, item) < 0) {
            temp = temp->right;
        } else if (temp->left != NULL && cmpf(temp->item, item) > 0) {
            temp = temp->left;
        }
    }

    if (cmpf(temp->item, item) > 0) {
        t_btree* new_elem = (t_btree*) calloc(1, sizeof(t_btree));
        if (new_elem != NULL) {
            temp->left = new_elem;
            new_elem->left = NULL;
            new_elem->right = NULL;
            new_elem->item = item;
        }
    } else if (cmpf(temp->item, item) < 0) {
        t_btree* new_elem = (t_btree*) calloc(1, sizeof(t_btree));
        if (new_elem != NULL) {
            temp->right = new_elem;
            new_elem->left = NULL;
            new_elem->right = NULL;
            new_elem->item = item;
        }
    }
}

void bstree_apply_infix(t_btree *root, void (*applyf)(int)) {
    if (root->left != NULL) {
        bstree_apply_infix(root->left, applyf);
    }
    applyf(root->item);
    if (root->right != NULL) {
        bstree_apply_infix(root->right, applyf);
    }
}

void bstree_apply_prefix(t_btree *root, void (*applyf)(int)) {
    applyf(root->item);
    if (root->left != NULL) {
        bstree_apply_prefix(root->left, applyf);
    }
    if (root->right != NULL) {
        bstree_apply_prefix(root->right, applyf);
    }
}

void bstree_apply_postfix(t_btree *root, void (*applyf)(int)) {
    if (root->right != NULL) {
        bstree_apply_postfix(root->right, applyf);
    }
    applyf(root->item);
    if (root->left != NULL) {
        bstree_apply_postfix(root->left, applyf);
    }
}

void destroy(t_btree* root) {
    if (root->left != NULL) {
        destroy(root->left);
    }
    free(root);
    if (root->right != NULL) {
        destroy(root->right);
    }
}
