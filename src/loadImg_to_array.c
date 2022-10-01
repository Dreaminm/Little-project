#include "../inc/header.h"

void loadToArray(SDL_Renderer *rend, SDL_Texture *img_array[], SDL_Texture **map_img) {
    img_array[0] = optimize("resource/img/start.png", rend);
    img_array[1] = optimize("resource/img/settings.png", rend);
    img_array[2] = optimize("resource/img/exit.png", rend);
    img_array[3] = optimize("resource/img/2_players.png", rend);
    img_array[4] = optimize("resource/img/3_players.png", rend);
    img_array[5] = optimize("resource/img/4_players.png", rend);
    img_array[6] = optimize("resource/img/max_screen.png", rend);
    img_array[7] = optimize("resource/img/mid_screen.png", rend);
    img_array[8] = optimize("resource/img/min_screen.png", rend);

    *map_img = optimize("resource/img/map.png", rend);
}

void loadBackgroundArray(SDL_Renderer *rend, SDL_Texture **menu_array, SDL_Texture **start_array, SDL_Texture **settings_background, SDL_Texture **quest_background) {
    *menu_array = optimize("resource/img/menu_1.png", rend);

    *start_array = optimize("resource/img/start_1.png", rend);

    *quest_background = optimize("resource/img/quest.png", rend);

    *settings_background = optimize("resource/img/settings_background.png", rend);
}
