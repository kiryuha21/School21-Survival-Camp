#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

size_t s21_strlen(const char* str);
int s21_strcmp(const char* first, const char* second);
char* s21_strcpy(char* restrict destination, const char *restrict source);
char* s21_strcat(char *restrict destination, const char *restrict source);
char* s21_strchr(const char* src, int sym);
char* s21_strstr(const char* haystack, const char* needle);
char* s21_strtok(char* restrict str, const char* restrict delim);

#endif  // SRC_S21_STRING_H_
