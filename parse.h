#ifndef SRC_PARSE_H_
#define SRC_PARSE_H_

#define ERR -1

int is_solo_char(char line);
int is_digit(char ch);
int handle_number(char* line, list** result, list** current, int* err);
void allocate_and_push(int size, list** result, list** current, char* position, int* err);
void push_unary(list** result, list** current, int* err);
char* handle_lexem(char* position, list** result, list** current, int* err);
list* parse_line(char* line, int* err);

#endif  // SRC_PARSE_H_
