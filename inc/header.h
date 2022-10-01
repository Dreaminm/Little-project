#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

typedef struct player{
    int x;
    int y;
    int pos;
    int money;
    int opened_chest;
    int skip;
}              player;

typedef struct card
{
    int x;
    int y;
    int cost;
    int index_p;
    bool key;
}card;



SDL_Texture *optimize(char *filepath, SDL_Renderer *rend);
void destroyTexture(SDL_Texture *texture);
SDL_Texture *loadFromRenderedText(TTF_Font *font, SDL_Renderer *rend, char *text, SDL_Color *color);
int font_init(TTF_Font **font_dited, TTF_Font **font_Elfboyclassic);
void loadToArray(SDL_Renderer *rend, SDL_Texture *img_array[], SDL_Texture **map_img);
void loadBackgroundArray(SDL_Renderer *rend, SDL_Texture **menu_array, SDL_Texture **start_array, SDL_Texture **settings_background, SDL_Texture **quest_background);
void change_rect(SDL_Rect *rect, int x, int y, int width, int height);
void setColor(SDL_Color *color, Uint8 a, Uint8 r, Uint8 g, Uint8 b);
void secondary_init(SDL_Rect *button1, SDL_Rect *button2, SDL_Rect *button3, SDL_Texture *current_buttons[], SDL_Texture *img_array[], int width, int height);
void primary_init(SDL_Rect *button1, SDL_Rect *button2, SDL_Rect *button3, SDL_Texture *current_buttons[], SDL_Texture *img_array[], int width, int height, int count);
void reload_rect(SDL_Rect *yes, SDL_Rect *no, SDL_Rect *aus, SDL_Rect *screen, int width, int height);
SDL_Texture *num_to_texture(TTF_Font *font, SDL_Renderer *rend, int num, SDL_Color *color);
int randCol();
int dice();
void map_mid_load(card *map, int width, int height);
void load_cost(card *map);
int keygen();
int rand_num();
void loadChests_to_array(SDL_Texture *array[], SDL_Renderer *rend);
bool fifty();



#endif
