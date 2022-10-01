#include "../inc/header.h"

void map_mid_load(card *map, int width, int height) {
    map[0].x = width - height + height / 14;
    map[0].y = height / 14;

    for (int i = 0; i < 36; i++)
    {
        if (i == 1 || i == 9)
        {
            map[i].x = map[i - 1].x + height / 14 + height / 22;
            map[i].y = map[i - 1].y;
        }
        else if (i > 1 && i < 9)
        {
            map[i].x = map[i - 1].x + height / 11;
            map[i].y = map[i - 1].y;
        }
        else if (i == 10 || i == 18)
        {
            map[i].x = map[i - 1].x;
            map[i].y = map[i - 1].y + height / 14 + height / 22;
        }
        else if (i > 10 && i < 18)
        {
            map[i].x = map[i - 1].x;
            map[i].y = map[i - 1].y + height / 11;          
        }
        else if (i == 19 || i == 27)
        {
            map[i].x = map[i - 1].x - height / 14 - height / 22;
            map[i].y = map[i - 1].y;
        }
        else if (i > 19 && i < 27)
        {
            map[i].x = map[i - 1].x - height / 11;
            map[i].y = map[i - 1].y;          
        }
        else if (i == 28)
        {
            map[i].x = map[i - 1].x;
            map[i].y = map[i - 1].y - height / 14 - height / 22;     
        }
        else if (i > 28 && i < 36)
        {
            map[i].x = map[i - 1].x;
            map[i].y = map[i - 1].y - height / 11;       
        }
    }
}

void load_cost(card *map) {
    for (int i = 0; i < 36; i++)
    {
        if (i > 0 && i < 9 && i != 3 && i != 7)
            map[i].cost = 300;
        else if (i > 9 && i < 18 && i != 12 && i != 14 && i != 16)
            map[i].cost = 400;
        else if (i > 18 && i < 27 && i != 20 && i != 22 && i != 24)
            map[i].cost = 100;
        else if (i > 27 && i < 36 && i != 29 && i != 33)
            map[i].cost = 200; 
        else
            map[i].cost = 0;
    }
    
}
