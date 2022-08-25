CC = gcc
FLAGS = -Wall -Werror -Wextra

print_module:
	$(CC) $(FLAGS) main_module_entry_point.c print_module.c -o ../build/Quest_1

documentation_module:
	$(CC) $(FLAGS) main_module_entry_point.c documentation_module.c print_module.c -o ../build/Quest_2 -D DOC

bst_create_test:
	$(CC) $(FLAGS) bst.c bst_create_test.c -o ../build/Quest_3

bst_insert_test:
	$(CC) $(FLAGS) bst.c bst_insert_test.c -o ../build/Quest_4

bst_traverse_test:
	$(CC) $(FLAGS) bst.c bst_traverse_test.c -o ../build/Quest_5
