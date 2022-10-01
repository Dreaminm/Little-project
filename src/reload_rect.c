#include "../inc/header.h"

void reload_rect(SDL_Rect *yes, SDL_Rect *no, SDL_Rect *aus, SDL_Rect *screen, int width, int height) {
    change_rect(yes, 4 * width / 10, 4 * height / 7, width / 25, height / 17);
    change_rect(no, (5 * width / 10) + width / 25, 4 * height / 7, width / 25, height / 17);                          
    change_rect(aus, 2 * width / 5, 3 * height / 7, width / 5, height / 7);
    change_rect(screen, 0, 0, width, height);
}
