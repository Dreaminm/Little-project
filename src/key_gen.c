#include "../inc/header.h"

int keygen()
{
    srand(time(0));
    int i = rand() % 36;
    return i;
}

int rand_num()
{
    int num[] = {50, 100, 150, 200, 250, 300, 350, 400, 450, 500};
    srand(time(0));
    int i = rand() % 10;
    return num[i];
}
