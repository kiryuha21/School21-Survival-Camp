#ifndef SRC_BST_H_
#define SRC_BST_H_

typedef struct s_btree {
    struct s_btree *left;
    struct s_btree *right;
    int             item;
} t_btree;

t_btree *bstree_create_node(int item);
int default_compare(int first, int second);
int digits_sum_compare(int first, int second);
void simple_print(int n);
void bstree_insert(t_btree *root, int item, int (*cmpf)(int, int));
void bstree_apply_infix(t_btree *root, void (*applyf)(int));
void bstree_apply_prefix(t_btree *root, void (*applyf)(int));
void bstree_apply_postfix(t_btree *root, void (*applyf)(int));
void destroy(t_btree* root);

#endif  // SRC_BST_H_
