#include "../inc/header.h"

void change_rect(SDL_Rect *rect, int x, int y, int width, int height) {
    rect->x = x;
    rect->y = y;
    rect->w = width;
    rect->h = height;
}
