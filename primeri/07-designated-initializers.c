#include <stdio.h>
#include <stdlib.h>

struct person {
    char *name;
    char *surname;
    short age;
};

enum color {
    RED, BLUE, GREEN, YELLOW, PURPLE, WHITE, BLACK
};

const char * const names[] = {
    [RED] = "red",
    [BLUE] = "blue",
    [GREEN] = "green",
    [PURPLE] = "purple",
    [WHITE] = "white",
    [BLACK] = "black"
};

int main() {
    struct person p = {
        .name = "Dusan",
        .surname = "Gvozdenovic",
        .age = 20
    };

    int array[100] = { [0 ... 9] = 1, [ 10 ... 99 ] = 2 };

    // Sta moze da se zapise krace u fajlu u-char.c?

    return 0;
}