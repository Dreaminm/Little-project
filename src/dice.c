#include "../inc/header.h"

int dice() {
    srand(time(0));
    int i = 1 + rand() % 6;
    return i;
}

bool fifty() {
    srand(time(0));
    return rand() % 2;
}
