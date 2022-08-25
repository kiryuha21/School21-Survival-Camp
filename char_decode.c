#include <stdio.h>

#define ERR -1
#define NEW_LINE 1

int my_atoi(const char *str) {
    int res = 0;

    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] > '9' || str[i] < '0') {
            return ERR;
        }
        res = res*10 + str[i] - '0';
    }

    return res;
}

int check_next() {
    int next_sym = getchar();
    if (next_sym == '\n') {
        return NEW_LINE;
    }
    if (next_sym != ' ') {
        return ERR;
    }
    return 0;
}

int encode() {
    char ch;
    while (scanf("%c", &ch) == 1) {
        if (ch == '\n') {
            return 0;
        }
        int check = check_next();
        if (check != 0) {
            if (check == NEW_LINE) {
                printf("%X", ch);
                return 0;
            }
            return ERR;
        }
        printf("%X ", ch);
    }
    return ERR;
}

int decode() {
    unsigned int hex;
    while (scanf("%x", &hex) == 1) {
        int check = check_next();
        if (check != 0) {
            if (check == NEW_LINE) {
                if (hex < 128) {
                    printf("%c", hex);
                    return 0;
                }
                return ERR;
            }
            return ERR;
        }
        printf("%c ", hex);
    }
    return ERR;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("n/a");
        return 0;
    }

    int option = my_atoi(argv[1]);
    if (option != 0 && option != 1) {
        printf("n/a");
        return 0;
    }

    if (option == 0) {
        if (encode() != 0) {
            printf("n/a");
            return 0;
        }
    } else {
        if (decode() != 0) {
            printf("n/a");
            return 0;
        }
    }

    return 0;
}
