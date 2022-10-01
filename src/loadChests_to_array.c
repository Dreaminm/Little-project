#include "../inc/header.h"

void loadChests_to_array(SDL_Texture *array[], SDL_Renderer *rend) {
    array[0] = optimize("resource/img/0 opened chests.png", rend);
    array[1] = optimize("resource/img/1 opened chest.png", rend);
    array[2] = optimize("resource/img/2 opened chests.png", rend);
    array[3] = optimize("resource/img/3 opened chests.png", rend);
    array[4] = optimize("resource/img/4 opened chests.png", rend);
}
