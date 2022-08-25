CC = gcc
FLAGS = -Wall -Werror -Wextra

all: state_sort state_search clear_state

state_sort:
	$(CC) $(FLAGS) utils.c state_sort.c -o ../build/Quest_1

state_search:
	$(CC) $(FLAGS) utils.c state_search.c -o ../build/Quest_2

clear_state:
	$(CC) $(FLAGS) utils.c clear_state.c -o ../build/Quest_3

run1:
	leaks -q -atExit -- ../build/Quest_1

run2:
	leaks -q -atExit -- ../build/Quest_2

run3:
	leaks -q -atExit -- ../build/Quest_3