#include <stdio.h>

#define ERR 1

int main() {
    int name;
    if (scanf("%d", &name) != 1 || getchar() != '\n') {
        puts("Non-integer value!");
        return ERR;
    }
    printf("Hello, %d!\n", name);
    return 0;
}