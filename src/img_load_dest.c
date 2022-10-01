#include "../inc/header.h"

SDL_Texture *optimize(char *filepath, SDL_Renderer *rend) {
    SDL_Texture *newTexture = NULL;
    SDL_Surface *loadedIMG = IMG_Load(filepath);
    
    if (loadedIMG == NULL)
    {
        printf("Unable to load %s! IMG_Error: %s\n", filepath, IMG_GetError());
        return NULL;
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface(rend, loadedIMG);

        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! IMG_Error: %s\n", filepath, IMG_GetError());
            return NULL;
        }
        SDL_FreeSurface(loadedIMG);
    }
    return newTexture;
}

void destroyTexture(SDL_Texture *texture) {
    SDL_DestroyTexture(texture);
}

SDL_Texture *loadFromRenderedText(TTF_Font *font, SDL_Renderer *rend, char *text, SDL_Color *color) {
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, *color);
    SDL_Texture *newTexture = NULL;

    if (textSurface == NULL)
    {
        printf("Unable to render text surface! TTF_Error: %s\n", TTF_GetError());
        return NULL;
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface(rend, textSurface);
        if (text == NULL)
        {
            printf("Unable to create texture from rendered text! TTF_Error: %s\n", TTF_GetError());
            return NULL;
        }
        
        SDL_FreeSurface(textSurface);
    }
    return newTexture;
}
