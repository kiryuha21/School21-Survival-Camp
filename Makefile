CC = gcc

FLAGS = -Wall -Werror -Wextra

SRC = \
	s21_string.c \
	s21_string_test.c

.PHONY: text_processor

strlen_tests:
	$(CC) $(FLAGS) $(SRC) -o ../build/Quest_1 -D STRLEN

strcmp_tests:
	$(CC) $(FLAGS) $(SRC) -o ../build/Quest_2 -D STRCMP

strcpy_tests:
	$(CC) $(FLAGS) $(SRC) -o ../build/Quest_3 -D STRCPY

strcat_tests:
	$(CC) $(FLAGS) $(SRC) -o ../build/Quest_4 -D STRCAT

strchr_tests:
	$(CC) $(FLAGS) $(SRC) -o ../build/Quest_5 -D STRCHR

strstr_tests:
	$(CC) $(FLAGS) $(SRC) -o ../build/Quest_6 -D STRSTR

strtok_tests:
	$(CC) $(FLAGS) $(SRC) -o ../build/Quest_7 -D STRTOK

all_tests:
	$(CC) $(FLAGS) $(SRC) -o ../build/all_tests -D STRLEN -D STRCMP -D STRCPY -D STRCAT -D STRCHR -D STRSTR -D STRTOK

text_processor:
	$(CC) $(FLAGS) s21_string.c text_processor.c -o ../build/Quest_8
