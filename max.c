#include <stdio.h>

#define ERR 1

int max(int first, int second) {
    if (first > second) {
        return first;
    }
    return second;
}

int main() {
    int first, second;
    if (scanf("%d%d", &first, &second) != 2 || getchar() != '\n') {
        puts("n/a");
        return ERR;
    }

    printf("%d\n", max(first, second));
    return 0;
}
