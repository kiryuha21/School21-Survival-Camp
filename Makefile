CC = gcc

FLAGS = -Wall -Werror -Wextra

TARGET = ../build/cipher

all: cipher logging_cipher

cipher:
	$(CC) $(FLAGS) cipher.c -o $(TARGET)

logging_cipher:
	$(CC) $(FLAGS) cipher.c logger.c -o ../build/logging_cipher -D LOG

run:
	leaks -q -atExit -- $(TARGET)