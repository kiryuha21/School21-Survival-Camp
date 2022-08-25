CC = gcc

FLAGS = -Wall -Werror -Wextra

SRC = \
		dynamics.c \
		graph.c \
		parse.c \
		polish_notation.c \
		main_utils.c

TARGET = ../build/graph

all:
	$(CC) $(FLAGS) $(SRC) -o $(TARGET)

no_flags:
	$(CC) $(SRC) -o $(TARGET)

run:
	$(TARGET)

run_leaks:
	leaks --quiet -atExit -- $(TARGET)
