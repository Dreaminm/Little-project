#include "../inc/header.h"

void primary_init(SDL_Rect *button1, SDL_Rect *button2, SDL_Rect *button3, SDL_Texture *current_buttons[], SDL_Texture *img_array[], int width, int height, int count) {
    for (int i = 0; i < 3; i++)
        current_buttons[i] = img_array[i + count];
    change_rect(button1, width / 2 - width / 5, height / 2 - height / 3, (width / 5) * 2, height / 8);
    change_rect(button2, width / 2 - width / 5, height / 2 - height / 10, (width / 5) * 2, height / 8);
    change_rect(button3, width / 2 - width / 5, height / 2 + height / 7, (width / 5) * 2, height / 8);
}
