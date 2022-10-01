#include "../inc/header.h"

void secondary_init(SDL_Rect *button1, SDL_Rect *button2, SDL_Rect *button3, SDL_Texture *current_buttons[], SDL_Texture *img_array[], int width, int height) {
    current_buttons[0] = img_array[1];
    current_buttons[1] = img_array[2];
    current_buttons[2] = NULL;
    change_rect(button1, width / 2 - width / 5, 2 * height / 6 - height / 12, (width / 5) * 2, height / 6);
    change_rect(button2, width / 2 - width / 5, 4 * height / 6 - height / 12, (width/ 5) * 2, height / 6);
    change_rect(button3, 0, 0, 0, 0);
}
