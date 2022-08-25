CC = gcc

FLAGS = -Wall -Werror -Wextra

SRC = \
		levels.c \
		modules.c \
		modules_db.c \
		shared.c \
		status_events.c \
		utils.c

TARGET = ../build/main

all: build run

build:
	$(CC) $(FLAGS) $(SRC) -o $(TARGET)

run:
	leaks -q -atExit -- $(TARGET)