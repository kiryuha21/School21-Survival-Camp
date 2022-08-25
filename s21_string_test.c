#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

void s21_strlen_test();
void s21_strcmp_test();
void s21_strcpy_test();
void s21_strcat_test();
void s21_strchr_test();
void s21_strstr_test();
void s21_strtok_test();

int main() {
#ifdef STRLEN
    s21_strlen_test();
#endif

#ifdef STRCMP
    s21_strcmp_test();
#endif

#ifdef STRCPY
    s21_strcpy_test();
#endif

#ifdef STRCAT
    s21_strcat_test();
#endif

#ifdef STRCHR
    s21_strchr_test();
#endif

#ifdef STRSTR
    s21_strstr_test();
#endif

#ifdef STRTOK
    s21_strtok_test();
#endif
    return 0;
}

void s21_strlen_test() {
    size_t res = s21_strlen("test");
    printf("IN - %s\n", "test");
    printf("OUT - %zu\n", res);
    printf("RESULT - %s\n\n", res == 4 ? "SUCCESS" : "FAIL");

    res = s21_strlen("");
    printf("IN - %s\n", "");
    printf("OUT - %zu\n", res);
    printf("RESULT - %s\n\n", res == 0 ? "SUCCESS" : "FAIL");

    res = s21_strlen("another test");
    printf("IN - %s\n", "another test");
    printf("OUT - %zu\n", res);
    printf("RESULT - %s\n\n", res == 12 ? "SUCCESS" : "FAIL");
}

void s21_strcmp_test() {
    int res = s21_strcmp("test", "test");
    printf("IN - %s %s\n", "test", "test");
    printf("OUT - %d\n", res);
    printf("RESULT - %s\n\n", res == 0 ? "SUCCESS" : "FAIL");

    res = s21_strcmp("test1", "test");
    printf("IN - %s %s\n", "test1", "test");
    printf("OUT - %d\n", res);
    printf("RESULT - %s\n\n", res == ('1' - '\0') ? "SUCCESS" : "FAIL");

    res = s21_strcmp("test", "test1");
    printf("IN - %s %s\n", "test", "test1");
    printf("OUT - %d\n", res);
    printf("RESULT - %s\n\n", res == ('\0' - '1') ? "SUCCESS" : "FAIL");

    res = s21_strcmp("test2", "test1");
    printf("IN - %s %s\n", "test2", "test1");
    printf("OUT - %d\n", res);
    printf("RESULT - %s\n\n", res == ('2' - '1') ? "SUCCESS" : "FAIL");

    res = s21_strcmp("", "");
    printf("IN - %s %s\n", "", "");
    printf("OUT - %d\n", res);
    printf("RESULT - %s\n\n", res == 0 ? "SUCCESS" : "FAIL");
}

void s21_strcpy_test() {
    size_t dst_size = s21_strlen("test");
    char* dst = (char*)calloc(dst_size + 1, sizeof(char));
    if (dst != NULL) {
        dst = s21_strcpy(dst, "test");
        printf("IN - %s\n", "test");
        printf("OUT - %s\n", dst);
        printf("RESULT - %s\n\n", s21_strcmp(dst, "test") == 0 ? "SUCCESS" : "FAIL");
        free(dst);
    } else {
        printf("memory allocation for test failed\n");
    }

    dst_size = s21_strlen("");
    dst = (char*)calloc(dst_size + 1, sizeof(char));
    if (dst != NULL) {
        dst = s21_strcpy(dst, "");
        printf("IN - %s\n", "");
        printf("OUT - %s\n", dst);
        printf("RESULT - %s\n\n", s21_strcmp(dst, "") == 0 ? "SUCCESS" : "FAIL");
        free(dst);
    } else {
        printf("memory allocation for test failed\n");
    }

    dst_size = s21_strlen("pretty long test");
    dst = (char*)calloc(dst_size + 1, sizeof(char));
    if (dst != NULL) {
        dst = s21_strcpy(dst, "pretty long test");
        printf("IN - %s\n", "pretty long test");
        printf("OUT - %s\n", dst);
        printf("RESULT - %s\n\n", s21_strcmp(dst, "pretty long test") == 0 ? "SUCCESS" : "FAIL");
        free(dst);
    } else {
        printf("memory allocation for test failed\n");
    }
}

void s21_strcat_test() {
    size_t src_size = s21_strlen("test");
    size_t dst_size = src_size + s21_strlen(" another");
    char* dst = (char*)calloc(dst_size + 1, sizeof(char));
    if (dst != NULL) {
        dst = s21_strcpy(dst, "test");
        dst = s21_strcat(dst, " another");
        printf("IN - %s %s\n", "test", " another");
        printf("OUT - %s\n", dst);
        printf("RESULT - %s\n\n", s21_strcmp(dst, "test another") == 0 ? "SUCCESS" : "FAIL");
        free(dst);
    } else {
        printf("memory allocation for test failed\n");
    }

    src_size = s21_strlen("");
    dst_size = src_size + s21_strlen("");
    dst = (char*)calloc(dst_size + 1, sizeof(char));
    if (dst != NULL) {
        dst = s21_strcpy(dst, "");
        dst = s21_strcat(dst, "");
        printf("IN - %s %s\n", "", "");
        printf("OUT - %s\n", dst);
        printf("RESULT - %s\n\n", s21_strcmp(dst, "") == 0 ? "SUCCESS" : "FAIL");
        free(dst);
    } else {
        printf("memory allocation for test failed\n");
    }

    src_size = s21_strlen("empty second");
    dst_size = src_size + s21_strlen("");
    dst = (char*)calloc(dst_size + 1, sizeof(char));
    if (dst != NULL) {
        dst = s21_strcpy(dst, "empty second");
        dst = s21_strcat(dst, "");
        printf("IN - %s %s\n", "empty second", "");
        printf("OUT - %s\n", dst);
        printf("RESULT - %s\n\n", s21_strcmp(dst, "empty second") == 0 ? "SUCCESS" : "FAIL");
        free(dst);
    } else {
        printf("memory allocation for test failed\n");
    }

    src_size = s21_strlen("");
    dst_size = src_size + s21_strlen("empty first");
    dst = (char*)calloc(dst_size + 1, sizeof(char));
    if (dst != NULL) {
        dst = s21_strcpy(dst, "");
        dst = s21_strcat(dst, "empty first");
        printf("IN - %s %s\n", "", " empty first");
        printf("OUT - %s\n", dst);
        printf("RESULT - %s\n\n", s21_strcmp(dst, "empty first") == 0 ? "SUCCESS" : "FAIL");
        free(dst);
    } else {
        printf("memory allocation for test failed\n");
    }
}

void s21_strchr_test() {
    char* res = s21_strchr("test", 'e');
    printf("IN - %s %c\n", "test", 'e');
    printf("OUT - %s\n", res);
    printf("RESULT - %s\n\n", s21_strcmp(res, "est") == 0 ? "SUCCESS" : "FAIL");

    res = s21_strchr("another test", 'e');
    printf("IN - %s %c\n", "another test", 'e');
    printf("OUT - %s\n", res);
    printf("RESULT - %s\n\n", s21_strcmp(res, "er test") == 0 ? "SUCCESS" : "FAIL");

    res = s21_strchr("test", 'a');
    printf("IN - %s %c\n", "test", 'a');
    printf("OUT - %s\n", res);
    printf("RESULT - %s\n\n", res == NULL ? "SUCCESS" : "FAIL");
}

void s21_strstr_test() {
    char* res = s21_strstr("test", "est");
    printf("IN - %s %s\n", "test", "est");
    printf("OUT - %s\n", res);
    printf("RESULT - %s\n\n", s21_strcmp(res, "est") == 0 ? "SUCCESS" : "FAIL");

    res = s21_strstr("testing test", "te");
    printf("IN - %s %s\n", "testing test", "te");
    printf("OUT - %s\n", res);
    printf("RESULT - %s\n\n", s21_strcmp(res, "testing test") == 0 ? "SUCCESS" : "FAIL");

    res = s21_strstr("test", "null");
    printf("IN - %s %s\n", "test", "null");
    printf("OUT - %s\n", res);
    printf("RESULT - %s\n\n", res == NULL ? "SUCCESS" : "FAIL");
}

void s21_strtok_test() {
    char* expected1[3] = {"this", "is", "test"};
    char* input = (char*)calloc(s21_strlen("this;is;test"), sizeof(char));
    if (input != NULL) {
        s21_strcpy(input, "this;is;test");
        printf("IN - %s\n", input);
        char *temp = s21_strtok(input, ";");
        int res = 1;
        printf("OUT - \n");
        for (int i = 0; i < 3 && temp != NULL && res; ++i) {
            printf("%s\n", temp);
            if (s21_strcmp(temp, expected1[i]) != 0) {
                res = 0;
            } else {
                temp = s21_strtok(NULL, ";");
            }
        }
        printf("RESULT - %s\n\n", res ? "SUCCESS" : "FAIL");
        free(input);
    } else {
        printf("memory allocation for test failed\n");
    }

    char* expected2[3] = {"multi", "separator", "test"};
    input = (char*)calloc(s21_strlen("multi-separator test"), sizeof(char));
    if (input != NULL) {
        s21_strcpy(input, "multi-separator test");
        printf("IN - %s\n", input);
        char *temp = s21_strtok(input, "- ");
        int res = 1;
        printf("OUT - \n");
        for (int i = 0; i < 3 && temp != NULL && res; ++i) {
            printf("%s\n", temp);
            if (s21_strcmp(temp, expected2[i]) != 0) {
                res = 0;
            } else {
                temp = s21_strtok(NULL, "- ");
            }
        }
        printf("RESULT - %s\n\n", res ? "SUCCESS" : "FAIL");
        free(input);
    } else {
        printf("memory allocation for test failed\n");
    }

    char* expected3[3] = {"overseparated", "text", "here"};
    input = (char*)calloc(s21_strlen("overseparated;;;;;text----here"), sizeof(char));
    if (input != NULL) {
        s21_strcpy(input, "overseparated;;;;;text----here");
        printf("IN - %s\n", input);
        char *temp = s21_strtok(input, ";-");
        int res = 1;
        printf("OUT - \n");
        for (int i = 0; i < 3 && temp != NULL && res; ++i) {
            printf("%s\n", temp);
            if (s21_strcmp(temp, expected3[i]) != 0) {
                res = 0;
            } else {
                temp = s21_strtok(NULL, ";-");
            }
        }
        printf("RESULT - %s\n\n", res ? "SUCCESS" : "FAIL");
        free(input);
    } else {
        printf("memory allocation for test failed\n");
    }

    input = (char*)calloc(s21_strlen("non-separatable text"), sizeof(char));
    if (input != NULL) {
        s21_strcpy(input, "non-separatable text");
        printf("IN - %s\n", input);
        char *temp = s21_strtok(input, ";");
        temp = s21_strtok(NULL, ";");
        printf("OUT - %s\n", temp);
        printf("RESULT - %s\n", *temp == '\0' ? "SUCCESS" : "FAIL");
        free(input);
    } else {
        printf("memory allocation for test failed\n");
    }
}
