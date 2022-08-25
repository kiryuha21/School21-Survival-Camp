CC = gcc
FLAGS = -Wall -Werror -Wextra

door_struct:
	$(CC) $(FLAGS) dmanager_module.c -o ../build/Quest_1

list_test:
	$(CC) $(FLAGS) list.c list_test.c -o ../build/Quest_2

stack_test:
	$(CC) $(FLAGS) stack.c stack_test.c -o ../build/Quest_3