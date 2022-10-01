#ifndef CHARAC_H
#define CHARAC_H

#include "header.h"

int SCREEN_WIDTH = 1080;
int SCREEN_HEIGHT = 720;

SDL_Window *win = NULL;
SDL_Renderer *rend = NULL;
SDL_Texture *current_img = NULL;
SDL_Texture *img_array[9];
SDL_Texture *current_buttons[3];
SDL_Texture *start_array;
SDL_Texture *settings_background;
SDL_Texture *quest_background;
SDL_Texture *menu_array;
SDL_Texture *map_img = NULL;
SDL_Texture *key = NULL;
SDL_Texture *leave = NULL;
SDL_Texture *agry = NULL;
SDL_Texture *disagry = NULL;
SDL_Texture *point1 = NULL;
SDL_Texture *point2 = NULL;
SDL_Texture *point3 = NULL;
SDL_Texture *point4 = NULL;
SDL_Texture *currdice = NULL;
SDL_Texture *massege = NULL;
SDL_Texture *ui_2 = NULL;
SDL_Texture *ui_3 = NULL;
SDL_Texture *ui_4 = NULL;
SDL_Texture *dicee[6];
SDL_Texture *homes[4];
SDL_Texture *chests[5];
SDL_Texture *chances[6];
SDL_Texture *currchan = NULL;
SDL_Texture *wkey = NULL;
SDL_Texture *winners[4];
SDL_Texture *winner = NULL;
SDL_Color orange;
SDL_Color color;
SDL_Color black;
TTF_Font *font_dited = NULL;
TTF_Font *font_Elfboyclassic = NULL;

card map[36];

bool escape = false;
bool start = false;
bool settings = false;
bool game_is_started = false;
bool menu_is_open = false;
bool quest = false;
bool turn1 = true;
bool turn2 = false;
bool turn3 = false;
bool turn4 = false;
bool tur1 = false;
bool tur2 = false;
bool tur3 = false;
bool tur4 = false;
bool mes1 = false;
bool mes2 = false;
bool mes3 = false;
bool mes4 = false;
bool winn = false;
int players = 0;
int num = 0;
int key_int;


#endif
