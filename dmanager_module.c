#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "door_struct.h"

#define DOORS_COUNT 15
#define MAX_ID_SEED 10000

int main() {
    struct door doors[DOORS_COUNT];

    initialize_doors(doors);

    sort_doors(doors);
    set_status(doors);

    print_doors(doors);

    return 0;
}

void print_doors(struct door* doors) {
    for (int i = 0; i < DOORS_COUNT - 1; ++i) {
        printf("%d, %d\n", doors[i].id, doors[i].status);
    }
    printf("%d, %d", doors[DOORS_COUNT - 1].id, doors[DOORS_COUNT - 1].status);
}

void swap(struct door* first, struct door* second) {
    struct door temp = *first;
    *first = *second;
    *second = temp;
}

void set_status(struct door* doors) {
    for (int i = 0; i < DOORS_COUNT; ++i) {
        doors[i].status = 0;
    }
}

void sort_doors(struct door* doors) {
    for (int i = 0; i < DOORS_COUNT - 1; ++i) {
        for (int j = 0; j < DOORS_COUNT - i - 1; ++j) {
            if (doors[j + 1].id < doors[j].id) {
                swap(&doors[j + 1], &doors[j]);
            }
        }
    }
}

// Doors initialization function
// ATTENTION!!!
// DO NOT CHANGE!
void initialize_doors(struct door* doors) {
    srand(time(0));

    int seed = rand() % MAX_ID_SEED;
    for (int i = 0; i < DOORS_COUNT; i++) {
        doors[i].id = (i + seed) % DOORS_COUNT;
        doors[i].status = rand() % 2;
    }
}
