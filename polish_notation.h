#ifndef SRC_POLISH_NOTATION_H_
#define SRC_POLISH_NOTATION_H_

#include "dynamics.h"

#define ERR -1

#define LOW_P  1
#define HIGH_P 2

stack* handle_binary(stack* head, list** result, list** curr, char* lexem);
int get_priority(char* lexem);
int is_prefix(char* lexem);
int is_binary(char* lexem);
int is_num(char* lexem);
double apply_binary(double_stack** main_stack, char* lexem);
double apply_prefix(double_stack** main_stack, char* lexem);

list* parse_to_polish(list* lexems, int* err);
double apply_polish(double x, list* parsed_polish, int* err);

#endif  // SRC_POLISH_NOTATION_H_
