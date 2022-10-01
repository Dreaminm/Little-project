#include "../inc/header.h"

int font_init(TTF_Font **font_dited, TTF_Font **font_Elfboyclassic) {
    *font_dited = TTF_OpenFont("resource/fonts/dited.ttf", 14);
    *font_Elfboyclassic = TTF_OpenFont("resource/fonts/Elfboyclassic.ttf", 14);

    if (*font_dited == NULL)
    {
        printf("Could not load %s font! TTF_Error:%s\n", "dited", TTF_GetError());
        return -1;
    }
    if (*font_Elfboyclassic == NULL)
    {
        printf("Could not load %s font! TTF_Error:%s\n", "Elfboyclassic", TTF_GetError());
        return -1;
    }
    return 0;
}

void setColor(SDL_Color *color, Uint8 a, Uint8 r, Uint8 g, Uint8 b) {
    color->a = a;
    color->r = r;
    color->g = g;
    color->b = b;
}

int randCol()
{
    int i = rand() % 256;
    return i;
}
