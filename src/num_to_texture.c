#include "../inc/header.h"

SDL_Texture *num_to_texture(TTF_Font *font, SDL_Renderer *rend, int num, SDL_Color *color) {
    char *c;
    int count = 0;
    int temp = num;
    int res;

    if (num == 0)
    {
        c = (char*)malloc(sizeof(char) * 3);
        c[2] = '\0';
        c[1] = '$';
        c[0] = '0';
        SDL_Texture *newTexture = loadFromRenderedText(font, rend, c, color);
        return newTexture;
    }
    

    while (temp != 0)
    {
        temp /= 10;
        count++;
    }
    c = (char*)malloc(sizeof(char) * (count + 2));
    res = count + 2;
    c[count + 1] = '\0';
    c[count] = '$';
    for (int i = 2; i < res; i++)
    {
        char t = num % 10 + '0';
        num /= 10;
        c[res - i - 1] = t;
    }
    
    
    SDL_Texture *newTexture = loadFromRenderedText(font, rend, c, color);
    return newTexture;
}
