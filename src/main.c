#include "../inc/header.h"
#include "../inc/charac.h"

int init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        return -1;
    }
    
    win = SDL_CreateWindow("Pummel Polly", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (win == NULL)
    {
        return -1;
    }

    rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    if (rend == NULL)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());        
        return -1;
    }
    else
    {
        SDL_SetRenderDrawColor(rend, 0xFF, 0xFF, 0xFF, 0xFF);
        int imgFlag = IMG_INIT_PNG | IMG_INIT_JPG;
        if (!(IMG_Init(imgFlag) & imgFlag))
        {
            printf("Img lib could not be initialize! SDL_Error: %s\n", SDL_GetError());
            return -1;
        }
        else
        {
            if (!TTF_WasInit())
            {
                if (TTF_Init() < 0)
                {
                    printf("TTF could not be initialize! TTF_Error: %s]n", TTF_GetError());
                }
            }
        }
    }
    return 0;
}

void quit() {
    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(rend);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main() {
    if (init() == -1)
    {
        return -1;
    }
    if (font_init(&font_dited, &font_Elfboyclassic) == -1)
    {
        return -1;
    }
    
    setColor(&color, 255, 255, 255, 255);
    setColor(&black, 255, 0, 0, 0);
    setColor(&orange, 255, 210, 105, 30);
    SDL_Event e;    
    SDL_Texture *leave = optimize("resource/img/Are_you_shure.png", rend);
    SDL_Texture *turn_1 = loadFromRenderedText(font_dited, rend, "Turn player 1", &black);
    SDL_Texture *turn_2 = loadFromRenderedText(font_dited, rend, "Turn player 2", &black);
    SDL_Texture *turn_3 = loadFromRenderedText(font_dited, rend, "Turn player 3", &black);
    SDL_Texture *turn_4 = loadFromRenderedText(font_dited, rend, "Turn player 4", &black);
    SDL_Texture *prentr = loadFromRenderedText(font_dited, rend, "Press enter", &black);
    SDL_Texture *want_you = optimize("resource/img/do_you_want.png", rend);
    SDL_Texture *dmoney = optimize("resource/img/No money.png", rend);
    homes[0] = optimize("resource/img/Red house.png", rend);
    homes[1] = optimize("resource/img/Green house.png", rend);
    homes[2] = optimize("resource/img/Blue house.png", rend);
    homes[3] = optimize("resource/img/Yellow house.png", rend);

    player one;
    one.pos = 0;
    one.money = 700;
    one.opened_chest = 0;
    one.skip = 0;
    player two;
    two.pos = 0;
    two.money = 700;
    two.opened_chest = 0;
    two.skip = 0;
    player three;
    three.pos = 0;
    three.money = 700;
    three.opened_chest = 0;
    three.skip = 0;
    player four;
    four.pos = 0;
    four.money = 700;
    four.opened_chest = 0;
    four.skip = 0;
    
    SDL_Texture *player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
    SDL_Rect player_1_balance;
    change_rect(&player_1_balance, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 8, SCREEN_HEIGHT / 6 - SCREEN_HEIGHT / 12 + 1, (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, SCREEN_HEIGHT / 28);
    SDL_Texture *player_2_info_balance = num_to_texture(font_dited, rend, one.money, &black);
    SDL_Rect player_2_balance;
    change_rect(&player_2_balance, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 8, 2 * SCREEN_HEIGHT / 6 - SCREEN_HEIGHT / 70, (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, SCREEN_HEIGHT / 28);
    SDL_Texture *player_3_info_balance = num_to_texture(font_dited, rend, one.money, &black);
    SDL_Rect player_3_balance;
    change_rect(&player_3_balance, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 8, 5 * SCREEN_HEIGHT / 8 - SCREEN_HEIGHT / 14, (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, SCREEN_HEIGHT / 28);
    SDL_Texture *player_4_info_balance = num_to_texture(font_dited, rend, one.money, &black);
    SDL_Rect player_4_balance;
    change_rect(&player_4_balance, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 8, 7 * SCREEN_HEIGHT / 8 - SCREEN_HEIGHT / 11 + 1, (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, SCREEN_HEIGHT / 28);

    loadChests_to_array(chests, rend);
    loadBackgroundArray(rend, &menu_array, &start_array, &settings_background, &quest_background);
    loadToArray(rend, img_array, &map_img);
    current_img = menu_array;

    SDL_Texture *player_1_info_chests = chests[one.opened_chest];
    SDL_Rect player_1_chests;
    change_rect(&player_1_chests, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 - (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, SCREEN_HEIGHT / 8 + SCREEN_HEIGHT / 128, (SCREEN_WIDTH - SCREEN_HEIGHT) / 4 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 6 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 128, SCREEN_HEIGHT / 16);
    SDL_Texture *player_2_info_chests = chests[two.opened_chest];
    SDL_Rect player_2_chests;
    change_rect(&player_2_chests, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 - (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, 3 * SCREEN_HEIGHT / 8 - SCREEN_HEIGHT / 96, (SCREEN_WIDTH - SCREEN_HEIGHT) / 4 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 6 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 128, SCREEN_HEIGHT / 16);
    SDL_Texture *player_3_info_chests = chests[three.opened_chest];
    SDL_Rect player_3_chests;
    change_rect(&player_3_chests, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 - (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, 5 * SCREEN_HEIGHT / 8 - SCREEN_HEIGHT / 38, (SCREEN_WIDTH - SCREEN_HEIGHT) / 4 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 6 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 128, SCREEN_HEIGHT / 16);
    SDL_Texture *player_4_info_chests = chests[four.opened_chest];
    SDL_Rect player_4_chests;
    change_rect(&player_4_chests, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 - (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, 7 * SCREEN_HEIGHT / 8 - SCREEN_HEIGHT / 24, (SCREEN_WIDTH - SCREEN_HEIGHT) / 4 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 6 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 128, SCREEN_HEIGHT / 16);

    SDL_Rect home;
    SDL_Rect screen;
    change_rect(&screen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_Rect button1;
    change_rect(&button1, SCREEN_WIDTH / 2 - SCREEN_WIDTH / 5, SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 3, (SCREEN_WIDTH / 5) * 2, SCREEN_HEIGHT / 8);
    SDL_Rect button2;
    change_rect(&button2, SCREEN_WIDTH / 2 - SCREEN_WIDTH / 5, SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 10, (SCREEN_WIDTH / 5) * 2, SCREEN_HEIGHT / 8);
    SDL_Rect button3;
    change_rect(&button3, SCREEN_WIDTH / 2 - SCREEN_WIDTH / 5, SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 7, (SCREEN_WIDTH / 5) * 2, SCREEN_HEIGHT / 8);
    SDL_Rect aus;
    change_rect(&aus, 2 * SCREEN_WIDTH / 5 - SCREEN_WIDTH / 10, 2 * SCREEN_HEIGHT / 6, 2 * SCREEN_WIDTH / 5, 2 * SCREEN_HEIGHT / 7);
    SDL_Rect tur;
    change_rect(&tur, SCREEN_WIDTH - SCREEN_HEIGHT + (SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 8), SCREEN_HEIGHT / 8 + 50, SCREEN_HEIGHT / 4, 100);
    SDL_Rect prent;
    change_rect(&prent, SCREEN_WIDTH - SCREEN_HEIGHT + (SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 8), SCREEN_HEIGHT / 2 + 100, SCREEN_HEIGHT / 4, 100);
    SDL_Rect want_buy;
    change_rect(&want_buy, SCREEN_WIDTH / 2 - SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    SDL_Rect rect_chance;
    change_rect(&rect_chance, SCREEN_WIDTH / 2 - SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 4, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2);
    map_mid_load(map, SCREEN_WIDTH, SCREEN_HEIGHT);
    load_cost(map);

    key = optimize("resource/img/key.png", rend);
    point1 = optimize("resource/img/Knight.png", rend);
    point2 = optimize("resource/img/Sorcerer.png", rend);
    point3 = optimize("resource/img/Archer.png", rend);
    point4 = optimize("resource/img/Assassin.png", rend);
    dicee[0] = optimize("resource/img/1 Dice.png", rend);
    dicee[1] = optimize("resource/img/2 Dice.png", rend);
    dicee[2] = optimize("resource/img/3 Dice.png", rend);
    dicee[3] = optimize("resource/img/4 Dice.png", rend);
    dicee[4] = optimize("resource/img/5 Dice.png", rend);
    dicee[5] = optimize("resource/img/6 Dice.png", rend);
    chances[0] = optimize("resource/img/Get 50 money.png", rend);
    chances[1] = optimize("resource/img/Got 100 money.png", rend);
    chances[2] = optimize("resource/img/Got 150 money.png", rend);
    chances[3] = optimize("resource/img/Lost 50 money.png", rend);
    chances[4] = optimize("resource/img/Lost 100 money.png", rend);
    chances[5] = optimize("resource/img/Lost 150 money.png", rend);
    winners[0] = optimize("resource/img/Player_1_won.png", rend);
    winners[1] = optimize("resource/img/Player_2_won.png", rend);
    winners[2] = optimize("resource/img/Player_3_won.png", rend);
    winners[3] = optimize("resource/img/Player_4_won.png", rend);
    wkey = optimize("resource/img/Want_key.png", rend);

    key_int = keygen();
    map[key_int].key = true;
    
    ui_2 = optimize("resource/img/2_players_ui.png", rend);
    ui_3 = optimize("resource/img/3_players_ui.png", rend);
    ui_4 = optimize("resource/img/4_players_ui.png", rend);
    SDL_Rect ui_main;
    change_rect(&ui_main, 0, 0, SCREEN_WIDTH - SCREEN_HEIGHT, SCREEN_HEIGHT);
    
    SDL_Rect key_gen;
    change_rect(&key_gen, map[key_int].x - SCREEN_HEIGHT / 32, map[key_int].y - SCREEN_HEIGHT / 72, SCREEN_HEIGHT / 16, SCREEN_HEIGHT / 36);
    SDL_Rect diice;
    change_rect(&diice, (SCREEN_WIDTH - SCREEN_HEIGHT) + SCREEN_HEIGHT / 2 - 50, SCREEN_HEIGHT / 2 - 50, 100, 100);
    SDL_Rect pl1;
    change_rect(&pl1, map[0].x, map[0].y, SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27);
    SDL_Rect pl2;
    change_rect(&pl2, map[0].x - SCREEN_HEIGHT / 27, map[0].y, SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27);
    SDL_Rect pl3;
    change_rect(&pl3, map[0].x - SCREEN_HEIGHT / 27, map[0].y - SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27);
    SDL_Rect pl4;
    change_rect(&pl4, map[0].x, map[0].y - SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27);

    for (int  i = 0; i < 3; i++)
        current_buttons[i] = img_array[i];

    while (!escape)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                escape = true;
                game_is_started = false;
                change_rect(&screen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                current_img = menu_array;
            }
            else if (e.key.keysym.sym == SDLK_ESCAPE && SDL_KEYDOWN == e.type)
            {
                if ((start && !game_is_started) || (settings && !game_is_started))
                {
                    start = false;
                    settings = false;
                    current_img = menu_array;
                    for (int i = 0; i < 3; i++)
                        current_buttons[i] = img_array[i];
                }
                else if (game_is_started)
                {
                    if (menu_is_open && !settings && !quest)
                    {
                        menu_is_open = false;
                        change_rect(&screen, SCREEN_WIDTH - SCREEN_HEIGHT, 0, SCREEN_HEIGHT, SCREEN_HEIGHT);
                        current_img = map_img;
                    }
                    else if (menu_is_open && quest && !settings)
                    {
                        quest = false;
                        current_img = menu_array;
                        secondary_init(&button1, &button2, &button3, current_buttons, img_array, SCREEN_WIDTH, SCREEN_HEIGHT);                     
                    }
                    else if (menu_is_open && settings && !quest)
                    {
                        settings = false;
                        current_img = menu_array;
                        secondary_init(&button1, &button2, &button3, current_buttons, img_array, SCREEN_WIDTH, SCREEN_HEIGHT);                     
                    }
                    else if (!menu_is_open)
                    {
                        menu_is_open = true;
                        change_rect(&screen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                        current_img = menu_array;
                    } 
                }
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN )
            {
                if (SDL_BUTTON_LEFT == e.button.button)
                {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if (((x > SCREEN_WIDTH / 2 - SCREEN_WIDTH / 5 && x < SCREEN_WIDTH / 2 - SCREEN_WIDTH / 5 + (SCREEN_WIDTH / 5) * 2) 
                        && (y > SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 3 && y < SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 3 + SCREEN_HEIGHT / 8))
                        && !game_is_started)
                    {
                        if (!start && !settings)
                        {
                            start = true;
                            current_img = start_array;
                            for (int i = 0; i < 3; i++)
                                current_buttons[i] = img_array[i + 3];
                        }
                        else if (start && !settings)
                        {
                            change_rect(&screen, SCREEN_WIDTH - SCREEN_HEIGHT, 0, SCREEN_HEIGHT, SCREEN_HEIGHT);
                            current_img = map_img;
                            start = false;
                            game_is_started = true;
                            players = 2;
                            secondary_init(&button1, &button2, &button3, current_buttons, img_array, SCREEN_WIDTH, SCREEN_HEIGHT);                          
                        }
                        else if (settings && !start)
                        {
                            settings = false;
                            quit();
                            SCREEN_WIDTH = 1440;
                            SCREEN_HEIGHT = 900;
                            init();
                            font_init(&font_dited, &font_Elfboyclassic);
                            loadChests_to_array(chests, rend);
                            loadBackgroundArray(rend, &menu_array, &start_array, &settings_background, &quest_background);
                            loadToArray(rend, img_array, &map_img);
                            setColor(&color, 255, 255, 255, 255);
                            setColor(&orange, 255, 210, 105, 30);
                            leave = optimize("resource/img/Are_you_shure.png", rend);
                            change_rect(&aus, 2 * SCREEN_WIDTH / 5, 3 * SCREEN_HEIGHT / 7, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 7);
                            change_rect(&diice, (SCREEN_WIDTH - SCREEN_HEIGHT) + SCREEN_HEIGHT / 2 - 50, SCREEN_HEIGHT / 2 - 50, 100, 100);
                            player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                            change_rect(&player_1_balance, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 8, SCREEN_HEIGHT / 6 - SCREEN_HEIGHT / 12 + 1, (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, SCREEN_HEIGHT / 28);
                            player_2_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                            change_rect(&player_2_balance, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 8, 2 * SCREEN_HEIGHT / 6 - SCREEN_HEIGHT / 70, (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, SCREEN_HEIGHT / 28);
                            player_3_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                            change_rect(&player_3_balance, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 8, 5 * SCREEN_HEIGHT / 8 - SCREEN_HEIGHT / 14, (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, SCREEN_HEIGHT / 28);
                            player_4_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                            change_rect(&player_4_balance, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 8, 7 * SCREEN_HEIGHT / 8 - SCREEN_HEIGHT / 11 + 1, (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, SCREEN_HEIGHT / 28);
                            player_1_info_chests = chests[one.opened_chest];
                            change_rect(&player_1_chests, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 - (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, SCREEN_HEIGHT / 8 + SCREEN_HEIGHT / 128, (SCREEN_WIDTH - SCREEN_HEIGHT) / 4 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 6 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 128, SCREEN_HEIGHT / 16);
                            player_2_info_chests = chests[two.opened_chest];
                            change_rect(&player_2_chests, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 - (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, 3 * SCREEN_HEIGHT / 8 - SCREEN_HEIGHT / 96, (SCREEN_WIDTH - SCREEN_HEIGHT) / 4 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 6 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 128, SCREEN_HEIGHT / 16);
                            player_3_info_chests = chests[three.opened_chest];
                            change_rect(&player_3_chests, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 - (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, 5 * SCREEN_HEIGHT / 8 - SCREEN_HEIGHT / 38, (SCREEN_WIDTH - SCREEN_HEIGHT) / 4 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 6 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 128, SCREEN_HEIGHT / 16);
                            player_4_info_chests = chests[four.opened_chest];
                            change_rect(&player_4_chests, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 - (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, 7 * SCREEN_HEIGHT / 8 - SCREEN_HEIGHT / 24, (SCREEN_WIDTH - SCREEN_HEIGHT) / 4 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 6 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 128, SCREEN_HEIGHT / 16);
                            ui_2 = optimize("resource/img/2_players_ui.png", rend);
                            ui_3 = optimize("resource/img/3_players_ui.png", rend);
                            ui_4 = optimize("resource/img/4_players_ui.png", rend);
                            change_rect(&ui_main, 0, 0, SCREEN_WIDTH - SCREEN_HEIGHT, SCREEN_HEIGHT);
                            wkey = optimize("resource/img/Want_key.png", rend);
                            winners[0] = optimize("resource/img/Player_1_won.png", rend);
                            winners[1] = optimize("resource/img/Player_2_won.png", rend);
                            winners[2] = optimize("resource/img/Player_3_won.png", rend);
                            winners[3] = optimize("resource/img/Player_4_won.png", rend);
                            map_mid_load(map, SCREEN_WIDTH, SCREEN_HEIGHT);
                            point1 = optimize("resource/img/Knight.png", rend);
                            point2 = optimize("resource/img/Sorcerer.png", rend);
                            point3 = optimize("resource/img/Archer.png", rend);
                            point4 = optimize("resource/img/Assassin.png", rend);
                            dicee[0] = optimize("resource/img/1 Dice.png", rend);
                            dicee[1] = optimize("resource/img/2 Dice.png", rend);
                            dicee[2] = optimize("resource/img/3 Dice.png", rend);
                            dicee[3] = optimize("resource/img/4 Dice.png", rend);
                            dicee[4] = optimize("resource/img/5 Dice.png", rend);
                            dicee[5] = optimize("resource/img/6 Dice.png", rend);
                            turn_1 = loadFromRenderedText(font_dited, rend, "Turn player 1", &black);
                            turn_2 = loadFromRenderedText(font_dited, rend, "Turn player 2", &black);
                            turn_3 = loadFromRenderedText(font_dited, rend, "Turn player 3", &black);
                            turn_4 = loadFromRenderedText(font_dited, rend, "Turn player 4", &black);
                            prentr = loadFromRenderedText(font_dited, rend, "Press enter", &black);
                            want_you = optimize("resource/img/do_you_want.png", rend);
                            dmoney = optimize("resource/img/No money.png", rend);
                            key = optimize("resource/img/key.png", rend);
                            homes[0] = optimize("resource/img/Red house.png", rend);
                            homes[1] = optimize("resource/img/Green house.png", rend);
                            homes[2] = optimize("resource/img/Blue house.png", rend);
                            homes[3] = optimize("resource/img/Yellow house.png", rend);
                            chances[0] = optimize("resource/img/Get 50 money.png", rend);
                            chances[1] = optimize("resource/img/Got 100 money.png", rend);
                            chances[2] = optimize("resource/img/Got 150 money.png", rend);
                            chances[3] = optimize("resource/img/Lost 50 money.png", rend);
                            chances[4] = optimize("resource/img/Lost 100 money.png", rend);
                            chances[5] = optimize("resource/img/Lost 150 money.png", rend);
                            one.x = map[one.pos].x;
                            one.y = map[one.pos].y;
                            two.x = map[two.pos].x;
                            two.y = map[two.pos].y;
                            three.x = map[three.pos].x;
                            three.y = map[three.pos].y;
                            four.x = map[four.pos].x;
                            four.y = map[four.pos].y;
                            change_rect(&pl1, one.x, one.y, SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27);
                            change_rect(&pl2, two.x - SCREEN_HEIGHT / 27, two.y, SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27);
                            change_rect(&pl3, three.x - SCREEN_HEIGHT / 27, three.y - SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27);
                            change_rect(&pl4, four.x, four.y - SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27);
                            change_rect(&screen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                            change_rect(&key_gen, map[key_int].x - SCREEN_HEIGHT / 32, map[key_int].y - SCREEN_HEIGHT / 72, SCREEN_HEIGHT / 16, SCREEN_HEIGHT / 36);
                            change_rect(&tur, SCREEN_WIDTH - SCREEN_HEIGHT + (SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 7), SCREEN_HEIGHT / 8 + 50, SCREEN_HEIGHT / 4, 100);
                            change_rect(&prent, SCREEN_WIDTH - SCREEN_HEIGHT + (SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 7), SCREEN_HEIGHT / 2 + 100, SCREEN_HEIGHT / 4, 100);
                            change_rect(&want_buy, SCREEN_WIDTH / 2 - SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
                            current_img = menu_array;
                            primary_init(&button1, &button2, &button3, current_buttons, img_array, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
                        }
                    }
                    else if ((x > SCREEN_WIDTH / 2 - SCREEN_WIDTH / 5 && x < SCREEN_WIDTH / 2 - SCREEN_WIDTH / 5 + (SCREEN_WIDTH / 5) * 2) 
                        && (y > SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 10 && y < SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 10 + SCREEN_HEIGHT / 8)
                            && !game_is_started)
                    {
                        if (!start && !settings)
                        {
                            current_img = settings_background;
                            settings = true;
                            for (int i = 0; i < 3; i++)
                                current_buttons[i] = img_array[i + 6];
                        }
                        else if (start && !settings)
                        {
                            change_rect(&screen, SCREEN_WIDTH - SCREEN_HEIGHT, 0, SCREEN_HEIGHT, SCREEN_HEIGHT);
                            current_img = map_img;
                            start = false;
                            game_is_started = true;
                            players = 3;
                            secondary_init(&button1, &button2, &button3, current_buttons, img_array, SCREEN_WIDTH, SCREEN_HEIGHT);
                        }
                        else if (settings && !start)
                        {
                            settings = false;
                            quit();
                            SCREEN_WIDTH = 1080;
                            SCREEN_HEIGHT = 720;
                            init();
                            font_init(&font_dited, &font_Elfboyclassic);
                            loadChests_to_array(chests, rend);
                            loadBackgroundArray(rend, &menu_array, &start_array, &settings_background, &quest_background);
                            loadToArray(rend, img_array, &map_img);
                            setColor(&color, 255, 255, 255, 255);
                            setColor(&orange, 255, 210, 105, 30);                      
                            leave = optimize("resource/img/Are_you_shure.png", rend);
                            change_rect(&aus, 2 * SCREEN_WIDTH / 5, 3 * SCREEN_HEIGHT / 7, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 7);
                            change_rect(&diice, (SCREEN_WIDTH - SCREEN_HEIGHT) + SCREEN_HEIGHT / 2 - 50, SCREEN_HEIGHT / 2 - 50, 100, 100);
                            player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                            change_rect(&player_1_balance, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 8, SCREEN_HEIGHT / 6 - SCREEN_HEIGHT / 12 + 1, (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, SCREEN_HEIGHT / 28);
                            player_2_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                            change_rect(&player_2_balance, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 8, 2 * SCREEN_HEIGHT / 6 - SCREEN_HEIGHT / 70, (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, SCREEN_HEIGHT / 28);
                            player_3_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                            change_rect(&player_3_balance, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 8, 5 * SCREEN_HEIGHT / 8 - SCREEN_HEIGHT / 14, (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, SCREEN_HEIGHT / 28);
                            player_4_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                            change_rect(&player_4_balance, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 8, 7 * SCREEN_HEIGHT / 8 - SCREEN_HEIGHT / 11 + 1, (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, SCREEN_HEIGHT / 28);
                            player_1_info_chests = chests[one.opened_chest];
                            change_rect(&player_1_chests, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 - (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, SCREEN_HEIGHT / 8 + SCREEN_HEIGHT / 128, (SCREEN_WIDTH - SCREEN_HEIGHT) / 4 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 6 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 128, SCREEN_HEIGHT / 16);
                            player_2_info_chests = chests[two.opened_chest];
                            change_rect(&player_2_chests, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 - (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, 3 * SCREEN_HEIGHT / 8 - SCREEN_HEIGHT / 96, (SCREEN_WIDTH - SCREEN_HEIGHT) / 4 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 6 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 128, SCREEN_HEIGHT / 16);
                            player_3_info_chests = chests[three.opened_chest];
                            change_rect(&player_3_chests, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 - (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, 5 * SCREEN_HEIGHT / 8 - SCREEN_HEIGHT / 38, (SCREEN_WIDTH - SCREEN_HEIGHT) / 4 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 6 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 128, SCREEN_HEIGHT / 16);
                            player_4_info_chests = chests[four.opened_chest];
                            change_rect(&player_4_chests, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 - (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, 7 * SCREEN_HEIGHT / 8 - SCREEN_HEIGHT / 24, (SCREEN_WIDTH - SCREEN_HEIGHT) / 4 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 6 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 128, SCREEN_HEIGHT / 16);
                            ui_2 = optimize("resource/img/2_players_ui.png", rend);
                            ui_3 = optimize("resource/img/3_players_ui.png", rend);
                            ui_4 = optimize("resource/img/4_players_ui.png", rend);
                            change_rect(&ui_main, 0, 0, SCREEN_WIDTH - SCREEN_HEIGHT, SCREEN_HEIGHT);
                            wkey = optimize("resource/img/Want_key.png", rend);
                            winners[0] = optimize("resource/img/Player_1_won.png", rend);
                            winners[1] = optimize("resource/img/Player_2_won.png", rend);
                            winners[2] = optimize("resource/img/Player_3_won.png", rend);
                            winners[3] = optimize("resource/img/Player_4_won.png", rend);
                            map_mid_load(map, SCREEN_WIDTH, SCREEN_HEIGHT);
                            point1 = optimize("resource/img/Knight.png", rend);
                            point2 = optimize("resource/img/Sorcerer.png", rend);
                            point3 = optimize("resource/img/Archer.png", rend);
                            point4 = optimize("resource/img/Assassin.png", rend);
                            dicee[0] = optimize("resource/img/1 Dice.png", rend);
                            dicee[1] = optimize("resource/img/2 Dice.png", rend);
                            dicee[2] = optimize("resource/img/3 Dice.png", rend);
                            dicee[3] = optimize("resource/img/4 Dice.png", rend);
                            dicee[4] = optimize("resource/img/5 Dice.png", rend);
                            dicee[5] = optimize("resource/img/6 Dice.png", rend);
                            turn_1 = loadFromRenderedText(font_dited, rend, "Turn player 1", &black);
                            turn_2 = loadFromRenderedText(font_dited, rend, "Turn player 2", &black);
                            turn_3 = loadFromRenderedText(font_dited, rend, "Turn player 3", &black);
                            turn_4 = loadFromRenderedText(font_dited, rend, "Turn player 4", &black);
                            prentr = loadFromRenderedText(font_dited, rend, "Press enter", &black);
                            want_you = optimize("resource/img/do_you_want.png", rend);
                            dmoney = optimize("resource/img/No money.png", rend);
                            key = optimize("resource/img/key.png", rend);
                            homes[0] = optimize("resource/img/Red house.png", rend);
                            homes[1] = optimize("resource/img/Green house.png", rend);
                            homes[2] = optimize("resource/img/Blue house.png", rend);
                            homes[3] = optimize("resource/img/Yellow house.png", rend);
                            chances[0] = optimize("resource/img/Get 50 money.png", rend);
                            chances[1] = optimize("resource/img/Got 100 money.png", rend);
                            chances[2] = optimize("resource/img/Got 150 money.png", rend);
                            chances[3] = optimize("resource/img/Lost 50 money.png", rend);
                            chances[4] = optimize("resource/img/Lost 100 money.png", rend);
                            chances[5] = optimize("resource/img/Lost 150 money.png", rend);
                            one.x = map[one.pos].x;
                            one.y = map[one.pos].y;
                            two.x = map[two.pos].x;
                            two.y = map[two.pos].y;
                            three.x = map[three.pos].x;
                            three.y = map[three.pos].y;
                            four.x = map[four.pos].x;
                            four.y = map[four.pos].y;
                            change_rect(&pl1, one.x, one.y, SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27);
                            change_rect(&pl2, two.x - SCREEN_HEIGHT / 27, two.y, SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27);
                            change_rect(&pl3, three.x - SCREEN_HEIGHT / 27, three.y - SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27);
                            change_rect(&pl4, four.x, four.y - SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27);
                            change_rect(&screen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                            change_rect(&key_gen, map[key_int].x - SCREEN_HEIGHT / 32, map[key_int].y - SCREEN_HEIGHT / 72, SCREEN_HEIGHT / 16, SCREEN_HEIGHT / 36);
                            change_rect(&tur, SCREEN_WIDTH - SCREEN_HEIGHT + (SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 8), SCREEN_HEIGHT / 8 + 50, SCREEN_HEIGHT / 4, 100);
                            change_rect(&prent, SCREEN_WIDTH - SCREEN_HEIGHT + (SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 8), SCREEN_HEIGHT / 2 + 100, SCREEN_HEIGHT / 4, 100);
                            change_rect(&want_buy, SCREEN_WIDTH / 2 - SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
                            current_img = menu_array;
                            primary_init(&button1, &button2, &button3, current_buttons, img_array, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
                        }                        
                    }
                    else if ((x > SCREEN_WIDTH / 2 - SCREEN_WIDTH / 5 && x < SCREEN_WIDTH / 2 - SCREEN_WIDTH / 5 + (SCREEN_WIDTH / 5) * 2) 
                            && (y > SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 7 && y < SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 7 + SCREEN_HEIGHT / 8)
                            && !game_is_started)
                    {
                        if (!start && !settings)
                        {
                            escape = true;
                            game_is_started = false;
                            change_rect(&screen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                            current_img = menu_array;
                        }
                        else if (start && !settings)
                        {
                            change_rect(&screen, SCREEN_WIDTH - SCREEN_HEIGHT, 0, SCREEN_HEIGHT, SCREEN_HEIGHT);
                            current_img = map_img;
                            start = false;
                            game_is_started = true;
                            players = 4;
                            secondary_init(&button1, &button2, &button3, current_buttons, img_array, SCREEN_WIDTH, SCREEN_HEIGHT);                         
                        }
                        else if (settings && !start)
                        {
                            settings = false;
                            quit();
                            SCREEN_WIDTH = 800;
                            SCREEN_HEIGHT = 600;
                            init();
                            font_init(&font_dited, &font_Elfboyclassic);
                            loadChests_to_array(chests, rend);
                            loadBackgroundArray(rend, &menu_array, &start_array, &settings_background, &quest_background);
                            loadToArray(rend, img_array, &map_img);
                            setColor(&color, 255, 255, 255, 255);
                            setColor(&orange, 255, 210, 105, 30);
                            leave = optimize("resource/img/Are_you_shure.png", rend);
                            change_rect(&aus, 2 * SCREEN_WIDTH / 5, 3 * SCREEN_HEIGHT / 7, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 7);
                            change_rect(&diice, (SCREEN_WIDTH - SCREEN_HEIGHT) + SCREEN_HEIGHT / 2 - 25, SCREEN_HEIGHT / 2 - 25, 50, 50);
                            player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                            change_rect(&player_1_balance, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 8, SCREEN_HEIGHT / 6 - SCREEN_HEIGHT / 12 + 1, (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, SCREEN_HEIGHT / 28);
                            player_2_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                            change_rect(&player_2_balance, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 8, 2 * SCREEN_HEIGHT / 6 - SCREEN_HEIGHT / 70, (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, SCREEN_HEIGHT / 28);
                            player_3_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                            change_rect(&player_3_balance, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 8, 5 * SCREEN_HEIGHT / 8 - SCREEN_HEIGHT / 14, (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, SCREEN_HEIGHT / 28);
                            player_4_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                            change_rect(&player_4_balance, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 8, 7 * SCREEN_HEIGHT / 8 - SCREEN_HEIGHT / 11 + 1, (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, SCREEN_HEIGHT / 28);
                            player_1_info_chests = chests[one.opened_chest];
                            change_rect(&player_1_chests, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 - (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, SCREEN_HEIGHT / 8 + SCREEN_HEIGHT / 128, (SCREEN_WIDTH - SCREEN_HEIGHT) / 4 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 6 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 128, SCREEN_HEIGHT / 16);
                            player_2_info_chests = chests[two.opened_chest];
                            change_rect(&player_2_chests, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 - (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, 3 * SCREEN_HEIGHT / 8 - SCREEN_HEIGHT / 96, (SCREEN_WIDTH - SCREEN_HEIGHT) / 4 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 6 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 128, SCREEN_HEIGHT / 16);
                            player_3_info_chests = chests[three.opened_chest];
                            change_rect(&player_3_chests, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 - (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, 5 * SCREEN_HEIGHT / 8 - SCREEN_HEIGHT / 38, (SCREEN_WIDTH - SCREEN_HEIGHT) / 4 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 6 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 128, SCREEN_HEIGHT / 16);
                            player_4_info_chests = chests[four.opened_chest];
                            change_rect(&player_4_chests, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 - (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, 7 * SCREEN_HEIGHT / 8 - SCREEN_HEIGHT / 24, (SCREEN_WIDTH - SCREEN_HEIGHT) / 4 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 6 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 128, SCREEN_HEIGHT / 16);
                            ui_2 = optimize("resource/img/2_players_ui.png", rend);
                            ui_3 = optimize("resource/img/3_players_ui.png", rend);
                            ui_4 = optimize("resource/img/4_players_ui.png", rend);
                            change_rect(&ui_main, 0, 0, SCREEN_WIDTH - SCREEN_HEIGHT, SCREEN_HEIGHT);
                            wkey = optimize("resource/img/Want_key.png", rend);
                            map_mid_load(map, SCREEN_WIDTH, SCREEN_HEIGHT);
                            point1 = optimize("resource/img/Knight.png", rend);
                            point2 = optimize("resource/img/Sorcerer.png", rend);
                            point3 = optimize("resource/img/Archer.png", rend);
                            point4 = optimize("resource/img/Assassin.png", rend);
                            dicee[0] = optimize("resource/img/1 Dice.png", rend);
                            dicee[1] = optimize("resource/img/2 Dice.png", rend);
                            dicee[2] = optimize("resource/img/3 Dice.png", rend);
                            dicee[3] = optimize("resource/img/4 Dice.png", rend);
                            dicee[4] = optimize("resource/img/5 Dice.png", rend);
                            dicee[5] = optimize("resource/img/6 Dice.png", rend);
                            turn_1 = loadFromRenderedText(font_dited, rend, "Turn player 1", &black);
                            turn_2 = loadFromRenderedText(font_dited, rend, "Turn player 2", &black);
                            turn_3 = loadFromRenderedText(font_dited, rend, "Turn player 3", &black);
                            turn_4 = loadFromRenderedText(font_dited, rend, "Turn player 4", &black);
                            prentr = loadFromRenderedText(font_dited, rend, "Press enter", &black);
                            want_you = optimize("resource/img/do_you_want.png", rend);
                            dmoney = optimize("resource/img/No money.png", rend);
                            key = optimize("resource/img/key.png", rend);
                            homes[0] = optimize("resource/img/Red house.png", rend);
                            homes[1] = optimize("resource/img/Green house.png", rend);
                            homes[2] = optimize("resource/img/Blue house.png", rend);
                            homes[3] = optimize("resource/img/Yellow house.png", rend);
                            chances[0] = optimize("resource/img/Get 50 money.png", rend);
                            chances[1] = optimize("resource/img/Got 100 money.png", rend);
                            chances[2] = optimize("resource/img/Got 150 money.png", rend);
                            chances[3] = optimize("resource/img/Lost 50 money.png", rend);
                            chances[4] = optimize("resource/img/Lost 100 money.png", rend);
                            chances[5] = optimize("resource/img/Lost 150 money.png", rend);
                            winners[0] = optimize("resource/img/Player_1_won.png", rend);
                            winners[1] = optimize("resource/img/Player_2_won.png", rend);
                            winners[2] = optimize("resource/img/Player_3_won.png", rend);
                            winners[3] = optimize("resource/img/Player_4_won.png", rend);
                            one.x = map[one.pos].x;
                            one.y = map[one.pos].y;
                            two.x = map[two.pos].x;
                            two.y = map[two.pos].y;
                            three.x = map[three.pos].x;
                            three.y = map[three.pos].y;
                            four.x = map[four.pos].x;
                            four.y = map[four.pos].y;
                            change_rect(&pl1, one.x, one.y, SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27);
                            change_rect(&pl2, two.x - SCREEN_HEIGHT / 27, two.y, SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27);
                            change_rect(&pl3, three.x - SCREEN_HEIGHT / 27, three.y - SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27);
                            change_rect(&pl4, four.x, four.y - SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27);
                            change_rect(&screen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                            change_rect(&key_gen, map[key_int].x - SCREEN_HEIGHT / 32, map[key_int].y - SCREEN_HEIGHT / 72, SCREEN_HEIGHT / 16, SCREEN_HEIGHT / 36);
                            change_rect(&tur, SCREEN_WIDTH - SCREEN_HEIGHT + (SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 8), SCREEN_HEIGHT / 8 + 50, SCREEN_HEIGHT / 4, 100);
                            change_rect(&prent, SCREEN_WIDTH - SCREEN_HEIGHT + (SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 8), SCREEN_HEIGHT / 2 + 100, SCREEN_HEIGHT / 4, 100);
                            change_rect(&want_buy, SCREEN_WIDTH / 2 - SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
                            current_img = menu_array;
                            primary_init(&button1, &button2, &button3, current_buttons, img_array, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
                        }                          
                    }
                    // первая из двух
                    else if ((x > SCREEN_WIDTH / 2 - SCREEN_WIDTH / 5 && x < SCREEN_WIDTH / 2 - SCREEN_WIDTH / 5 + (SCREEN_WIDTH / 5) * 2)
                            && (y > 2 * SCREEN_HEIGHT / 6 - SCREEN_HEIGHT / 12 && y < 2 * SCREEN_HEIGHT / 6 - SCREEN_HEIGHT / 12 + SCREEN_HEIGHT / 6)
                            && game_is_started && !settings && menu_is_open && !quest)
                    {
                        settings = true;
                        current_img = settings_background;
                        primary_init(&button1, &button2, &button3, current_buttons, img_array, SCREEN_WIDTH, SCREEN_HEIGHT, 6);
                    }
                    // вторая из двух
                    else if ((x > SCREEN_WIDTH / 2 - SCREEN_WIDTH / 5 && x < SCREEN_WIDTH / 2 - SCREEN_WIDTH / 5 + (SCREEN_WIDTH / 5) * 2)
                            && (y > 4 * SCREEN_HEIGHT / 6 - SCREEN_HEIGHT / 12 && y < 4 * SCREEN_HEIGHT / 6 - SCREEN_HEIGHT / 12 + SCREEN_HEIGHT / 6)
                            && game_is_started && !settings && menu_is_open && !quest)
                    {
                        quest = true;
                        current_img = quest_background;
                    }
                    else if ((x > SCREEN_WIDTH / 2.8 && x < SCREEN_WIDTH / 2)
                            && (y > SCREEN_HEIGHT / 2 && y < SCREEN_HEIGHT / 1.8)
                            && game_is_started && menu_is_open && quest)
                    {
                        start = false;
                        settings = false;
                        game_is_started = false;
                        menu_is_open = false;
                        quest = false;
                        current_img = menu_array;
                        primary_init(&button1, &button2, &button3, current_buttons, img_array, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
                        one.pos = 0;
                        one.money = 700;
                        two.pos = 0;
                        two.money = 700;
                        three.pos = 0;
                        three.money = 700; 
                        four.pos = 0;
                        four.money = 700;  
                        currdice = NULL; 
                        map[key_int].key = false; 
                        key_int = keygen();
                        map[key_int].key = true; 
                        one.x = map[one.pos].x;
                        one.y = map[one.pos].y;
                        two.x = map[two.pos].x;
                        two.y = map[two.pos].y;
                        three.x = map[three.pos].x;
                        three.y = map[three.pos].y;
                        four.x = map[four.pos].x;
                        four.y = map[four.pos].y;
                        one.skip = 0;
                        two.skip = 0;
                        three.skip = 0;
                        four.skip = 0;
                        turn1 = true;
                        turn2 = false;
                        turn3 = false;
                        turn4 = false;
                        tur1 = false;
                        tur2 = false;
                        tur3 = false;
                        tur4 = false;
                        mes1 = false;
                        mes2 = false;
                        mes3 = false;
                        mes4 = false;
                        winn = false;
                        for (int i = 0; i < 36; i++)
                        {
                            map[i].index_p = 0;
                            
                        }
                        change_rect(&pl1, one.x, one.y, 20, 20);
                        change_rect(&pl2, two.x - 20, two.y, 20, 20);
                        change_rect(&pl3, map[0].x - 20, map[0].y - 20, 20, 20);
                        change_rect(&pl4, map[0].x, map[0].y - 20, 20, 20); 
                        player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                        player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);            
                    }
                    else if ((x > SCREEN_WIDTH / 1.8 && x < SCREEN_WIDTH / 1.5)
                            && (y > SCREEN_HEIGHT / 2 && y < SCREEN_HEIGHT / 1.8)
                            && game_is_started && menu_is_open && quest)
                    {
                        quest = false;
                        current_img = menu_array;
                        secondary_init(&button1, &button2, &button3, current_buttons, img_array, SCREEN_WIDTH, SCREEN_HEIGHT);                      
                    }
                    else if ((x > SCREEN_WIDTH / 2 - SCREEN_WIDTH / 5 && x < SCREEN_WIDTH / 2 - SCREEN_WIDTH / 5 + (SCREEN_WIDTH / 5) * 2) 
                            && (y > SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 10 && y < SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 10 + SCREEN_HEIGHT / 8)
                            && game_is_started && settings && menu_is_open)
                    {
                        settings = false;
                        quit();
                        SCREEN_WIDTH = 1080;
                        SCREEN_HEIGHT = 720;
                        init();
                        font_init(&font_dited, &font_Elfboyclassic);
                        loadChests_to_array(chests, rend);
                        loadBackgroundArray(rend, &menu_array, &start_array, &settings_background, &quest_background);
                        loadToArray(rend, img_array, &map_img);
                        setColor(&color, 255, 255, 255, 255);
                        setColor(&orange, 255, 210, 105, 30);
                        leave = optimize("resource/img/Are_you_shure.png", rend);
                        change_rect(&aus, 2 * SCREEN_WIDTH / 5, 3 * SCREEN_HEIGHT / 7, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 7);
                        dicee[0] = optimize("resource/img/1 Dice.png", rend);
                        dicee[1] = optimize("resource/img/2 Dice.png", rend);
                        dicee[2] = optimize("resource/img/3 Dice.png", rend);
                        dicee[3] = optimize("resource/img/4 Dice.png", rend);
                        dicee[4] = optimize("resource/img/5 Dice.png", rend);
                        dicee[5] = optimize("resource/img/6 Dice.png", rend);
                        turn_1 = loadFromRenderedText(font_dited, rend, "Turn player 1", &black);
                        turn_2 = loadFromRenderedText(font_dited, rend, "Turn player 2", &black);
                        turn_3 = loadFromRenderedText(font_dited, rend, "Turn player 3", &black);
                        turn_4 = loadFromRenderedText(font_dited, rend, "Turn player 4", &black);
                        prentr = loadFromRenderedText(font_dited, rend, "Press enter", &black);
                        want_you = optimize("resource/img/do_you_want.png", rend);
                        dmoney = optimize("resource/img/No money.png", rend);
                        winners[0] = optimize("resource/img/Player_1_won.png", rend);
                        winners[1] = optimize("resource/img/Player_2_won.png", rend);
                        winners[2] = optimize("resource/img/Player_3_won.png", rend);
                        winners[3] = optimize("resource/img/Player_4_won.png", rend);
                        homes[0] = optimize("resource/img/Red house.png", rend);
                        homes[1] = optimize("resource/img/Green house.png", rend);
                        homes[2] = optimize("resource/img/Blue house.png", rend);
                        homes[3] = optimize("resource/img/Yellow house.png", rend);
                        chances[0] = optimize("resource/img/Get 50 money.png", rend);
                        chances[1] = optimize("resource/img/Got 100 money.png", rend);
                        chances[2] = optimize("resource/img/Got 150 money.png", rend);
                        chances[3] = optimize("resource/img/Lost 50 money.png", rend);
                        chances[4] = optimize("resource/img/Lost 100 money.png", rend);
                        chances[5] = optimize("resource/img/Lost 150 money.png", rend);
                        if (num != 0)
                            currdice = dicee[num - 1];
                        change_rect(&diice, (SCREEN_WIDTH - SCREEN_HEIGHT) + SCREEN_HEIGHT / 2 - 50, SCREEN_HEIGHT / 2 - 50, 100, 100);
                        change_rect(&screen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                        change_rect(&tur, SCREEN_WIDTH - SCREEN_HEIGHT + (SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 8), SCREEN_HEIGHT / 8 + 50, SCREEN_HEIGHT / 4, 100);
                        change_rect(&prent, SCREEN_WIDTH - SCREEN_HEIGHT + (SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 8), SCREEN_HEIGHT / 2 + 100, SCREEN_HEIGHT / 4, 100);
                        change_rect(&want_buy, SCREEN_WIDTH / 2 - SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
                        player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                        change_rect(&player_1_balance, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 8, SCREEN_HEIGHT / 6 - SCREEN_HEIGHT / 12 + 1, (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, SCREEN_HEIGHT / 28);
                        player_2_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                        change_rect(&player_2_balance, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 8, 2 * SCREEN_HEIGHT / 6 - SCREEN_HEIGHT / 70, (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, SCREEN_HEIGHT / 28);
                        player_3_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                        change_rect(&player_3_balance, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 8, 5 * SCREEN_HEIGHT / 8 - SCREEN_HEIGHT / 14, (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, SCREEN_HEIGHT / 28);
                        player_4_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                        change_rect(&player_4_balance, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 8, 7 * SCREEN_HEIGHT / 8 - SCREEN_HEIGHT / 11 + 1, (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, SCREEN_HEIGHT / 28);
                        player_1_info_chests = chests[one.opened_chest];
                        change_rect(&player_1_chests, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 - (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, SCREEN_HEIGHT / 8 + SCREEN_HEIGHT / 128, (SCREEN_WIDTH - SCREEN_HEIGHT) / 4 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 6 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 128, SCREEN_HEIGHT / 16);
                        player_2_info_chests = chests[two.opened_chest];
                        change_rect(&player_2_chests, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 - (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, 3 * SCREEN_HEIGHT / 8 - SCREEN_HEIGHT / 96, (SCREEN_WIDTH - SCREEN_HEIGHT) / 4 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 6 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 128, SCREEN_HEIGHT / 16);
                        player_3_info_chests = chests[three.opened_chest];
                        change_rect(&player_3_chests, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 - (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, 5 * SCREEN_HEIGHT / 8 - SCREEN_HEIGHT / 38, (SCREEN_WIDTH - SCREEN_HEIGHT) / 4 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 6 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 128, SCREEN_HEIGHT / 16);
                        player_4_info_chests = chests[four.opened_chest];
                        change_rect(&player_4_chests, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 - (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, 7 * SCREEN_HEIGHT / 8 - SCREEN_HEIGHT / 24, (SCREEN_WIDTH - SCREEN_HEIGHT) / 4 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 6 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 128, SCREEN_HEIGHT / 16);
                        ui_2 = optimize("resource/img/2_players_ui.png", rend);
                        ui_3 = optimize("resource/img/3_players_ui.png", rend);
                        ui_4 = optimize("resource/img/4_players_ui.png", rend);
                        change_rect(&ui_main, 0, 0, SCREEN_WIDTH - SCREEN_HEIGHT, SCREEN_HEIGHT);
                        wkey = optimize("resource/img/Want_key.png", rend);
                        map_mid_load(map, SCREEN_WIDTH, SCREEN_HEIGHT);
                        point1 = optimize("resource/img/Knight.png", rend);
                        point2 = optimize("resource/img/Sorcerer.png", rend);
                        point3 = optimize("resource/img/Archer.png", rend);
                        point4 = optimize("resource/img/Assassin.png", rend);
                        key = optimize("resource/img/key.png", rend);
                        one.x = map[one.pos].x;
                        one.y = map[one.pos].y;
                        two.x = map[two.pos].x;
                        two.y = map[two.pos].y;
                        three.x = map[three.pos].x;
                        three.y = map[three.pos].y;
                        four.x = map[four.pos].x;
                        four.y = map[four.pos].y;
                        change_rect(&pl1, one.x, one.y, SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27);
                        change_rect(&pl2, two.x - SCREEN_HEIGHT / 27, two.y, SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27);
                        change_rect(&pl3, three.x - SCREEN_HEIGHT / 27, three.y - SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27);
                        change_rect(&pl4, four.x, four.y - SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27);
                        change_rect(&key_gen, map[key_int].x - SCREEN_HEIGHT / 32, map[key_int].y - SCREEN_HEIGHT / 72, SCREEN_HEIGHT / 16, SCREEN_HEIGHT / 36);
                        current_img = menu_array;
                        secondary_init(&button1, &button2, &button3, current_buttons, img_array, SCREEN_WIDTH, SCREEN_HEIGHT);                                 
                    }
                    else if (((x > SCREEN_WIDTH / 2 - SCREEN_WIDTH / 5 && x < SCREEN_WIDTH / 2 - SCREEN_WIDTH / 5 + (SCREEN_WIDTH / 5) * 2) && (y > SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 7 && y < SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 7 + SCREEN_HEIGHT / 8))
                            && game_is_started && settings && menu_is_open)
                    {
                        settings = false;
                        quit();
                        SCREEN_WIDTH = 800;
                        SCREEN_HEIGHT = 600;
                        init();
                        font_init(&font_dited, &font_Elfboyclassic);
                        loadChests_to_array(chests, rend);
                        loadBackgroundArray(rend, &menu_array, &start_array, &settings_background, &quest_background);
                        loadToArray(rend, img_array, &map_img);
                        setColor(&color, 255, 255, 255, 255);
                        setColor(&orange, 255, 210, 105, 30);
                        leave = optimize("resource/img/Are_you_shure.png", rend);
                        change_rect(&aus, 2 * SCREEN_WIDTH / 5, 3 * SCREEN_HEIGHT / 7, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 7);
                        dicee[0] = optimize("resource/img/1 Dice.png", rend);
                        dicee[1] = optimize("resource/img/2 Dice.png", rend);
                        dicee[2] = optimize("resource/img/3 Dice.png", rend);
                        dicee[3] = optimize("resource/img/4 Dice.png", rend);
                        dicee[4] = optimize("resource/img/5 Dice.png", rend);
                        dicee[5] = optimize("resource/img/6 Dice.png", rend);
                        turn_1 = loadFromRenderedText(font_dited, rend, "Turn player 1", &black);
                        turn_2 = loadFromRenderedText(font_dited, rend, "Turn player 2", &black);
                        turn_3 = loadFromRenderedText(font_dited, rend, "Turn player 3", &black);
                        turn_4 = loadFromRenderedText(font_dited, rend, "Turn player 4", &black);
                        prentr = loadFromRenderedText(font_dited, rend, "Press enter", &black);
                        want_you = optimize("resource/img/do_you_want.png", rend);
                        dmoney = optimize("resource/img/No money.png", rend);
                        homes[0] = optimize("resource/img/Red house.png", rend);
                        homes[1] = optimize("resource/img/Green house.png", rend);
                        homes[2] = optimize("resource/img/Blue house.png", rend);
                        homes[3] = optimize("resource/img/Yellow house.png", rend);
                        winners[0] = optimize("resource/img/Player_1_won.png", rend);
                        winners[1] = optimize("resource/img/Player_2_won.png", rend);
                        winners[2] = optimize("resource/img/Player_3_won.png", rend);
                        winners[3] = optimize("resource/img/Player_4_won.png", rend);
                        chances[0] = optimize("resource/img/Get 50 money.png", rend);
                        chances[1] = optimize("resource/img/Got 100 money.png", rend);
                        chances[2] = optimize("resource/img/Got 150 money.png", rend);
                        chances[3] = optimize("resource/img/Lost 50 money.png", rend);
                        chances[4] = optimize("resource/img/Lost 100 money.png", rend);
                        chances[5] = optimize("resource/img/Lost 150 money.png", rend);
                        if (num != 0)
                            currdice = dicee[num - 1];  
                        change_rect(&diice, (SCREEN_WIDTH - SCREEN_HEIGHT) + SCREEN_HEIGHT / 2 - 25, SCREEN_HEIGHT / 2 - 25, 50, 50);                   
                        player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                        change_rect(&screen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                        change_rect(&player_1_balance, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 8, SCREEN_HEIGHT / 6 - SCREEN_HEIGHT / 12 + 1, (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, SCREEN_HEIGHT / 28);
                        player_2_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                        change_rect(&player_2_balance, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 8, 2 * SCREEN_HEIGHT / 6 - SCREEN_HEIGHT / 70, (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, SCREEN_HEIGHT / 28);
                        player_3_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                        change_rect(&player_3_balance, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 8, 5 * SCREEN_HEIGHT / 8 - SCREEN_HEIGHT / 14, (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, SCREEN_HEIGHT / 28);
                        player_4_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                        change_rect(&player_4_balance, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 8, 7 * SCREEN_HEIGHT / 8 - SCREEN_HEIGHT / 11 + 1, (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, SCREEN_HEIGHT / 28);
                        player_1_info_chests = chests[one.opened_chest];
                        change_rect(&player_1_chests, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 - (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, SCREEN_HEIGHT / 8 + SCREEN_HEIGHT / 128, (SCREEN_WIDTH - SCREEN_HEIGHT) / 4 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 6 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 128, SCREEN_HEIGHT / 16);
                        player_2_info_chests = chests[two.opened_chest];
                        change_rect(&player_2_chests, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 - (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, 3 * SCREEN_HEIGHT / 8 - SCREEN_HEIGHT / 96, (SCREEN_WIDTH - SCREEN_HEIGHT) / 4 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 6 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 128, SCREEN_HEIGHT / 16);
                        player_3_info_chests = chests[three.opened_chest];
                        change_rect(&player_3_chests, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 - (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, 5 * SCREEN_HEIGHT / 8 - SCREEN_HEIGHT / 38, (SCREEN_WIDTH - SCREEN_HEIGHT) / 4 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 6 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 128, SCREEN_HEIGHT / 16);
                        player_4_info_chests = chests[four.opened_chest];
                        change_rect(&player_4_chests, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 - (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, 7 * SCREEN_HEIGHT / 8 - SCREEN_HEIGHT / 24, (SCREEN_WIDTH - SCREEN_HEIGHT) / 4 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 6 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 128, SCREEN_HEIGHT / 16);
                        ui_2 = optimize("resource/img/2_players_ui.png", rend);
                        ui_3 = optimize("resource/img/3_players_ui.png", rend);
                        ui_4 = optimize("resource/img/4_players_ui.png", rend);
                        change_rect(&ui_main, 0, 0, SCREEN_WIDTH - SCREEN_HEIGHT, SCREEN_HEIGHT);
                        wkey = optimize("resource/img/Want_key.png", rend);
                        map_mid_load(map, SCREEN_WIDTH, SCREEN_HEIGHT);
                        point1 = optimize("resource/img/Knight.png", rend);
                        point2 = optimize("resource/img/Sorcerer.png", rend);
                        point3 = optimize("resource/img/Archer.png", rend);
                        point4 = optimize("resource/img/Assassin.png", rend);
                        key = optimize("resource/img/key.png", rend);
                        one.x = map[one.pos].x;
                        one.y = map[one.pos].y;
                        two.x = map[two.pos].x;
                        two.y = map[two.pos].y;
                        three.x = map[three.pos].x;
                        three.y = map[three.pos].y;
                        four.x = map[four.pos].x;
                        four.y = map[four.pos].y;
                        change_rect(&pl1, one.x, one.y, SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27);
                        change_rect(&pl2, two.x - SCREEN_HEIGHT / 27, two.y, SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27);
                        change_rect(&pl3, three.x - SCREEN_HEIGHT / 27, three.y - SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27);
                        change_rect(&pl4, four.x, four.y - SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27);
                        change_rect(&key_gen, map[key_int].x - SCREEN_HEIGHT / 32, map[key_int].y - SCREEN_HEIGHT / 72, SCREEN_HEIGHT / 16, SCREEN_HEIGHT / 36);
                        change_rect(&tur, SCREEN_WIDTH - SCREEN_HEIGHT + (SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 8), SCREEN_HEIGHT / 8 + 50, SCREEN_HEIGHT / 4, 100);
                        change_rect(&prent, SCREEN_WIDTH - SCREEN_HEIGHT + (SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 8), SCREEN_HEIGHT / 2 + 100, SCREEN_HEIGHT / 4, 100);
                        change_rect(&want_buy, SCREEN_WIDTH / 2 - SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
                        current_img = menu_array;
                        secondary_init(&button1, &button2, &button3, current_buttons, img_array, SCREEN_WIDTH, SCREEN_HEIGHT);                                        
                    }
                    else if ((x > SCREEN_WIDTH / 2 - SCREEN_WIDTH / 5 && x < SCREEN_WIDTH / 2 - SCREEN_WIDTH / 5 + (SCREEN_WIDTH / 5) * 2) && (y > SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 3 && y < SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 3 + SCREEN_HEIGHT / 8)
                            && game_is_started && settings && menu_is_open)
                    {
                        settings = false;
                        quit();
                        SCREEN_WIDTH = 1440;
                        SCREEN_HEIGHT = 900;
                        init();
                        font_init(&font_dited, &font_Elfboyclassic);
                        loadChests_to_array(chests, rend);
                        loadBackgroundArray(rend, &menu_array, &start_array, &settings_background, &quest_background);
                        loadToArray(rend, img_array, &map_img);
                        setColor(&color, 255, 255, 255, 255);
                        setColor(&orange, 255, 210, 105, 30);
                        leave = optimize("resource/img/Are_you_shure.png", rend);
                        change_rect(&aus, 2 * SCREEN_WIDTH / 5, 3 * SCREEN_HEIGHT / 7, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 7);
                        dicee[0] = optimize("resource/img/1 Dice.png", rend);
                        dicee[1] = optimize("resource/img/2 Dice.png", rend);
                        dicee[2] = optimize("resource/img/3 Dice.png", rend);
                        dicee[3] = optimize("resource/img/4 Dice.png", rend);
                        dicee[4] = optimize("resource/img/5 Dice.png", rend);
                        dicee[5] = optimize("resource/img/6 Dice.png", rend);
                        turn_1 = loadFromRenderedText(font_dited, rend, "Turn player 1", &black);
                        turn_2 = loadFromRenderedText(font_dited, rend, "Turn player 2", &black);
                        turn_3 = loadFromRenderedText(font_dited, rend, "Turn player 3", &black);
                        turn_4 = loadFromRenderedText(font_dited, rend, "Turn player 4", &black);
                        prentr = loadFromRenderedText(font_dited, rend, "Press enter", &black);
                        want_you = optimize("resource/img/do_you_want.png", rend);
                        dmoney = optimize("resource/img/No money.png", rend);
                        homes[0] = optimize("resource/img/Red house.png", rend);
                        homes[1] = optimize("resource/img/Green house.png", rend);
                        homes[2] = optimize("resource/img/Blue house.png", rend);
                        homes[3] = optimize("resource/img/Yellow house.png", rend);
                        winners[0] = optimize("resource/img/Player_1_won.png", rend);
                        winners[1] = optimize("resource/img/Player_2_won.png", rend);
                        winners[2] = optimize("resource/img/Player_3_won.png", rend);
                        winners[3] = optimize("resource/img/Player_4_won.png", rend);
                        chances[0] = optimize("resource/img/Get 50 money.png", rend);
                        chances[1] = optimize("resource/img/Got 100 money.png", rend);
                        chances[2] = optimize("resource/img/Got 150 money.png", rend);
                        chances[3] = optimize("resource/img/Lost 50 money.png", rend);
                        chances[4] = optimize("resource/img/Lost 100 money.png", rend);
                        chances[5] = optimize("resource/img/Lost 150 money.png", rend);
                        if (num != 0)
                            currdice = dicee[num - 1];                      
                        change_rect(&diice, (SCREEN_WIDTH - SCREEN_HEIGHT) + SCREEN_HEIGHT / 2 - 50, SCREEN_HEIGHT / 2 - 50, 100, 100);
                        player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                        change_rect(&screen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                        change_rect(&player_1_balance, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 8, SCREEN_HEIGHT / 6 - SCREEN_HEIGHT / 12 + 1, (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, SCREEN_HEIGHT / 28);
                        player_2_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                        change_rect(&player_2_balance, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 8, 2 * SCREEN_HEIGHT / 6 - SCREEN_HEIGHT / 70, (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, SCREEN_HEIGHT / 28);
                        player_3_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                        change_rect(&player_3_balance, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 8, 5 * SCREEN_HEIGHT / 8 - SCREEN_HEIGHT / 14, (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, SCREEN_HEIGHT / 28);
                        player_4_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                        change_rect(&player_4_balance, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 8, 7 * SCREEN_HEIGHT / 8 - SCREEN_HEIGHT / 11 + 1, (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, SCREEN_HEIGHT / 28);
                        player_1_info_chests = chests[one.opened_chest];
                        change_rect(&player_1_chests, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 - (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, SCREEN_HEIGHT / 8 + SCREEN_HEIGHT / 128, (SCREEN_WIDTH - SCREEN_HEIGHT) / 4 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 6 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 128, SCREEN_HEIGHT / 16);
                        player_2_info_chests = chests[two.opened_chest];
                        change_rect(&player_2_chests, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 - (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, 3 * SCREEN_HEIGHT / 8 - SCREEN_HEIGHT / 96, (SCREEN_WIDTH - SCREEN_HEIGHT) / 4 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 6 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 128, SCREEN_HEIGHT / 16);
                        player_3_info_chests = chests[three.opened_chest];
                        change_rect(&player_3_chests, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 - (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, 5 * SCREEN_HEIGHT / 8 - SCREEN_HEIGHT / 38, (SCREEN_WIDTH - SCREEN_HEIGHT) / 4 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 6 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 128, SCREEN_HEIGHT / 16);
                        player_4_info_chests = chests[four.opened_chest];
                        change_rect(&player_4_chests, (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 - (SCREEN_WIDTH - SCREEN_HEIGHT) / 10, 7 * SCREEN_HEIGHT / 8 - SCREEN_HEIGHT / 24, (SCREEN_WIDTH - SCREEN_HEIGHT) / 4 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 6 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 128, SCREEN_HEIGHT / 16);
                        ui_2 = optimize("resource/img/2_players_ui.png", rend);
                        ui_3 = optimize("resource/img/3_players_ui.png", rend);
                        ui_4 = optimize("resource/img/4_players_ui.png", rend);
                        change_rect(&ui_main, 0, 0, SCREEN_WIDTH - SCREEN_HEIGHT, SCREEN_HEIGHT);
                        wkey = optimize("resource/img/Want_key.png", rend);
                        map_mid_load(map, SCREEN_WIDTH, SCREEN_HEIGHT);
                        point1 = optimize("resource/img/Knight.png", rend);
                        point2 = optimize("resource/img/Sorcerer.png", rend);
                        point3 = optimize("resource/img/Archer.png", rend);
                        point4 = optimize("resource/img/Assassin.png", rend);
                        key = optimize("resource/img/key.png", rend);                        
                        one.x = map[one.pos].x;
                        one.y = map[one.pos].y;
                        two.x = map[two.pos].x;
                        two.y = map[two.pos].y;
                        three.x = map[three.pos].x;
                        three.y = map[three.pos].y;
                        four.x = map[four.pos].x;
                        four.y = map[four.pos].y;
                        change_rect(&pl1, one.x, one.y, SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27);
                        change_rect(&pl2, two.x - SCREEN_HEIGHT / 27, two.y, SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27);
                        change_rect(&pl3, three.x - SCREEN_HEIGHT / 27, three.y - SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27);
                        change_rect(&pl4, four.x, four.y - SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27);
                        change_rect(&key_gen, map[key_int].x - SCREEN_HEIGHT / 32, map[key_int].y - SCREEN_HEIGHT / 72, SCREEN_HEIGHT / 16, SCREEN_HEIGHT / 36);
                        change_rect(&tur, SCREEN_WIDTH - SCREEN_HEIGHT + (SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 7), SCREEN_HEIGHT / 8 + 50, SCREEN_HEIGHT / 4, 100);
                        change_rect(&prent, SCREEN_WIDTH - SCREEN_HEIGHT + (SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 7), SCREEN_HEIGHT / 2 + 100, SCREEN_HEIGHT / 4, 100);
                        change_rect(&want_buy, SCREEN_WIDTH / 2 - SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
                        current_img = menu_array;
                        secondary_init(&button1, &button2, &button3, current_buttons, img_array, SCREEN_WIDTH, SCREEN_HEIGHT);                                          
                    }
                }
            }  
            if (game_is_started && !menu_is_open && players == 2)
            {    
                if (e.key.keysym.sym == SDLK_RETURN && SDL_KEYUP == e.type && one.skip != 0 && turn1 && !tur1)
                {
                    massege = NULL;
                    currchan = NULL;
                    one.skip--;
                    turn1 = false;
                    tur1 = false;
                    turn2 = true;
                }
                else if(e.key.keysym.sym == SDLK_RETURN && SDL_KEYUP == e.type && turn1 && !tur1)
                {
                    massege = NULL;
                    currchan = NULL;

                    num = dice();
                    one.pos += num;
                    if (one.pos > 35)
                    {
                        one.pos -= 36;
                        one.money += 200;
                    }
                    one.x = map[one.pos].x;
                    one.y = map[one.pos].y;
                    currdice = dicee[num - 1];
                    change_rect(&pl1, one.x, one.y, SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27);
                    player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                    tur1 = true;
                }
                else if (map[one.pos].key == 1 && turn1 && tur1)
                {
                    massege = wkey;
                    if (e.key.keysym.sym == SDLK_y && SDL_KEYUP == e.type)
                    {
                        if (1000 > one.money)
                        {
                            massege = dmoney;
                            tur1 = false;
                            turn1 = false;
                            turn2 = true;
                        }
                        else
                        {
                            one.opened_chest++;
                            one.money -= 1000;
                            player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                            massege = NULL;
                            map[key_int].key = false;
                            key_int = keygen();
                            map[key_int].key = true;
                            change_rect(&key_gen, map[key_int].x - SCREEN_HEIGHT / 32, map[key_int].y - SCREEN_HEIGHT / 72, SCREEN_HEIGHT / 16, SCREEN_HEIGHT / 36);
                            player_1_info_chests = chests[one.opened_chest];
                            if (one.opened_chest == 4)
                                winn = true;
                            tur1 = false;
                            turn1 = false;
                            turn2 = true;
                        }
                    }
                    else if (e.key.keysym.sym == SDLK_n && SDL_KEYUP == e.type)
                    {
                        massege = NULL;
                        tur1 = false;
                        turn1 = false;
                        turn2 = true;
                    } 
                }
                else if (map[one.pos].cost != 0 && map[one.pos].index_p == 0 && turn1 && tur1)
                {
                    massege = want_you;
                    if (e.key.keysym.sym == SDLK_y && SDL_KEYUP == e.type)
                    {
                        if (map[one.pos].cost > one.money)
                        {
                            massege = dmoney;
                            tur1 = false;
                            turn1 = false;
                            turn2 = true;
                        }
                        else
                        {
                            map[one.pos].index_p = 1;
                            one.money -= map[one.pos].cost;
                            player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                            massege = NULL;
                            tur1 = false;
                            turn1 = false;
                            turn2 = true;
                        }
                    }
                    else if (e.key.keysym.sym == SDLK_n && SDL_KEYUP == e.type)
                    {
                        massege = NULL;
                        tur1 = false;
                        turn1 = false;
                        turn2 = true;
                    }
                }
                else if (map[one.pos].cost != 0 && map[one.pos].index_p == 2 && turn1 && tur1)
                {
                    if (one.money < map[one.pos].cost / 2)
                    {
                        two.money += one.money;
                        one.money = 0;
                        tur1 = false;
                        turn1 = false;
                        turn2 = true;
                        player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                        player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                    }
                    else{
                        two.money += map[one.pos].cost / 2;
                        one.money -= map[one.pos].cost / 2;
                        tur1 = false;
                        turn1 = false;
                        turn2 = true;
                        player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                        player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                    }
                }
                else if ((one.pos == 3 || one.pos == 29) && tur1 && turn1)
                {
                    if (one.money < 150)
                    {
                        one.money = 0;
                        tur1 = false;
                        turn1 = false;
                        turn2 = true;
                        player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                    }
                    else{
                        one.money -= 150;
                        tur1 = false;
                        turn1 = false;
                        turn2 = true;
                        player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                    }
                }
                else if ((one.pos == 12 || one.pos == 20 || one.pos == 33) && turn1 && tur1)
                {
                    one.money += rand_num();
                    tur1 = false;
                    turn1 = false;
                    turn2 = true;
                    player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                }
                else if (one.pos == 9 && turn1 && tur1)
                {
                    one.pos = 27;
                    one.skip = 4;
                    change_rect(&pl1, map[one.pos].x, map[one.pos].y, 20, 20);
                    tur1 = false;
                    turn1 = false;
                    turn2 = true;
                }
                else if (one.pos == 27 && turn1 && tur1)
                {
                    one.skip = 4;
                    tur1 = false;
                    turn1 = false;
                    turn2 = true;
                }
                else if (one.pos == 18 && turn1 && tur1)
                {
                    one.pos += 8;
                    one.money += 100;
                    tur1 = false;
                    turn1 = false;
                    turn2 = true;
                    player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                    change_rect(&pl1, map[one.pos].x, map[one.pos].y, 20, 20);

                }
                else if ((one.pos == 7 || one.pos == 16 || one.pos == 24) && turn1 && tur1 && e.key.keysym.sym == SDLK_RETURN && SDL_KEYUP == e.type)
                {
                    int cn = dice();
                    if (cn == 1)
                    {
                        one.money += 50;
                        currchan = chances[0];
                    }
                    else if (cn == 2)
                    {
                        one.money += 100;
                        currchan = chances[1];
                    }
                    else if (cn == 3)
                    {
                        one.money += 150;
                        currchan = chances[2];
                    }
                    else if (cn == 4)
                    {
                        one.money -= 50;
                        if (one.money < 0)
                            one.money = 0;
                        currchan = chances[3];
                    }
                    else if (cn == 5)
                    {
                        one.money -= 100;
                        if (one.money < 0)
                            one.money = 0;
                        currchan = chances[4];
                    }
                    else if (cn == 6)
                    {
                        one.money -= 150;
                        if (one.money < 0)
                            one.money = 0;
                        currchan = chances[5];
                    }
                    player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                    tur1 = false;
                    turn1 = false;
                    turn2 = true;
                }
                else if ((one.pos == 14 || one.pos == 22) && tur1 && turn1)
                {
                    if (one.pos == 14)
                    {
                        for (int i = 0; i < 36; i++)
                        {
                            if (map[i].index_p == 1)
                            {
                                if (fifty())
                                {
                                    map[i].index_p = 0;
                                    break;
                                }
                                else
                                    continue;
                            }
                        }
                        
                    }
                    else if (one.pos == 22)
                    {
                        for (int i = 0; i < 36; i++)
                        {
                            if (map[i].index_p == 1)
                                map[i].index_p = 0;
                        }
                    }
                    tur1 = false;
                    turn1 = false;
                    turn2 = true;
                }
                else if (one.pos == 0 && turn1 && tur1)
                {
                    tur1 = false;
                    turn1 = false;
                    turn2 = true;
                }
                else if (map[one.pos].cost != 0 && map[one.pos].index_p == 1 && turn1 && tur1)
                {
                    tur1 = false;
                    turn1 = false;
                    turn2 = true;
                }
                else if (e.key.keysym.sym == SDLK_RETURN && SDL_KEYUP == e.type && two.skip != 0 && turn2 && !tur2)
                {
                    massege = NULL;
                    currchan = NULL;
                    two.skip--;
                    turn2 = false;
                    tur2 = false;
                    turn1 = true;
                }
                else if(e.key.keysym.sym == SDLK_RETURN && SDL_KEYUP == e.type && turn2 && !tur2)
                {
                    massege = NULL;
                    currchan = NULL;
                    num = dice();
                    two.pos += num;
                    if (two.pos > 35)
                    {
                        two.pos -= 36;
                        two.money += 200;
                    }
                    two.x = map[two.pos].x;
                    two.y = map[two.pos].y;
                    currdice = dicee[num - 1];
                    change_rect(&pl2, two.x - SCREEN_HEIGHT / 27, two.y, SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27);
                    player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                    tur2 = true;
                }
                else if (map[two.pos].key == 1 && turn2 && tur2)
                {
                    massege = wkey;
                    if (e.key.keysym.sym == SDLK_y && SDL_KEYUP == e.type)
                    {
                        if (1000 > two.money)
                        {
                            massege = dmoney;
                            tur2 = false;
                            turn2 = false;
                            turn1 = true;
                        }
                        else
                        {
                            two.opened_chest++;
                            two.money -= 1000;
                            player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                            massege = NULL;
                            map[key_int].key = false;
                            key_int = keygen();
                            map[key_int].key = true;
                            change_rect(&key_gen, map[key_int].x - SCREEN_HEIGHT / 32, map[key_int].y - SCREEN_HEIGHT / 72, SCREEN_HEIGHT / 16, SCREEN_HEIGHT / 36);
                            player_2_info_chests = chests[two.opened_chest];
                            if (two.opened_chest == 4)
                                winn = true;
                            tur2 = false;
                            turn2 = false;
                            turn1 = true;
                        }
                    }
                    else if (e.key.keysym.sym == SDLK_n && SDL_KEYUP == e.type)
                    {
                        massege = NULL;
                        tur2 = false;
                        turn2 = false;
                        turn1 = true;
                    }
                }
                else if (map[two.pos].cost != 0 && map[two.pos].index_p == 0 && turn2 && tur2)
                {
                    massege = want_you;
                    if (e.key.keysym.sym == SDLK_y && SDL_KEYUP == e.type)
                    {
                        if (map[two.pos].cost > two.money)
                        {
                            massege = dmoney;
                            tur2 = false;
                            turn2 = false;
                            turn1 = true;
                        }
                        else
                        {
                            map[two.pos].index_p = 2;
                            two.money -= map[two.pos].cost;
                            player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                            massege = NULL;
                            tur2 = false;
                            turn2 = false;
                            turn1 = true;
                        }
                    }
                    else if (e.key.keysym.sym == SDLK_n && SDL_KEYUP == e.type)
                    {
                        massege = NULL;
                        tur2 = false;
                        turn2 = false;
                        turn1 = true;
                    }
                }
                else if (map[two.pos].cost != 0 && map[two.pos].index_p == 1 && turn2 && tur2)
                {
                    if (two.money < map[two.pos].cost / 2)
                    {
                        one.money += two.money;
                        two.money = 0;
                        tur2 = false;
                        turn2 = false;
                        turn1 = true;
                        player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                        player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                    }
                    else{
                        one.money += map[two.pos].cost / 2;
                        two.money -= map[two.pos].cost / 2;
                        tur2 = false;
                        turn2 = false;
                        turn1 = true;
                        player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                        player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                    }
                }
                else if ((two.pos == 3 || two.pos == 29) && tur2 && turn2)
                {
                    if (two.money < 150)
                    {
                        two.money = 0;
                        tur2 = false;
                        turn2 = false;
                        turn1 = true;
                        player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                    }
                    else{
                        two.money -= 150;
                        tur2 = false;
                        turn2 = false;
                        turn1 = true;
                        player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                    }
                }
                else if ((two.pos == 12 || two.pos == 20 || two.pos == 33) && turn2 && tur2)
                {
                    two.money += rand_num();
                    tur2 = false;
                    turn2 = false;
                    turn1 = true;
                    player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                }
                else if (two.pos == 9 && turn2 && tur2)
                {
                    two.pos = 27;
                    two.skip = 4;
                    change_rect(&pl2, map[two.pos].x - 20, map[two.pos].y, 20, 20);
                    tur2 = false;
                    turn2 = false;
                    turn1 = true;
                }
                else if (two.pos == 27 && turn2 && tur2)
                {
                    two.skip = 4;
                    tur2 = false;
                    turn2 = false;
                    turn1 = true;
                }
                else if (two.pos == 18 && turn2 && tur2)
                {
                    two.pos += 8;
                    two.money += 100;
                    tur2 = false;
                    turn2 = false;
                    turn1 = true;
                    player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                    change_rect(&pl2, map[two.pos].x - 20, map[two.pos].y, 20, 20);

                }
                else if ((two.pos == 7 || two.pos == 16 || two.pos == 24) && turn2 && tur2 && e.key.keysym.sym == SDLK_RETURN && SDL_KEYUP == e.type )
                {
                    int cn = dice();
                    if (cn == 1)
                    {
                        two.money += 50;
                        currchan = chances[0];
                    }
                    else if (cn == 2)
                    {
                        two.money += 100;
                        currchan = chances[1];
                    }
                    else if (cn == 3)
                    {
                        two.money += 150;
                        currchan = chances[2];
                    }
                    else if (cn == 4)
                    {
                        two.money -= 50;
                        if (two.money < 0)
                            two.money = 0;
                        currchan = chances[3];
                    }
                    else if (cn == 5)
                    {
                        two.money -= 100;
                        if (two.money < 0)
                            two.money = 0;
                        currchan = chances[4];
                    }
                    else if (cn == 6)
                    {
                        two.money -= 150;
                        if (two.money < 0)
                            two.money = 0;
                        currchan = chances[5];
                    }
                    player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                    tur2 = false;
                    turn2 = false;
                    turn1 = true;
                }
                else if ((two.pos == 14 || two.pos == 22) && tur2 && turn2)
                {
                    if (two.pos == 14)
                    {
                        for (int i = 0; i < 36; i++)
                        {
                            if (map[i].index_p == 2)
                            {
                                if (fifty())
                                {
                                    map[i].index_p = 0;
                                    break;
                                }
                                else
                                    continue;
                            }
                        }
                        
                    }
                    else if (two.pos == 22)
                    {
                        for (int i = 0; i < 36; i++)
                        {
                            if (map[i].index_p == 2)
                                map[i].index_p = 0;
                        }
                    }
                    tur2 = false;
                    turn2 = false;
                    turn1 = true;
                }
                else if (two.pos == 0 && tur2 && turn2)
                {
                    tur2 = false;
                    turn2 = false;
                    turn1 = true;
                }
                else if (map[two.pos].cost != 0 && map[two.pos].index_p == 2 && turn2 && tur2)
                {
                    tur2 = false;
                    turn2 = false;
                    turn1 = true;
                }
            }
            else if (game_is_started && !menu_is_open && players == 3) {
                if (e.key.keysym.sym == SDLK_RETURN && SDL_KEYUP == e.type && one.skip != 0 && turn1 && !tur1)
                {
                    massege = NULL;
                    currchan = NULL;
                    one.skip--;
                    turn1 = false;
                    tur1 = false;
                    turn2 = true;
                }
                else if(e.key.keysym.sym == SDLK_RETURN && SDL_KEYUP == e.type && turn1 && !tur1)
                {
                    massege = NULL;
                    currchan = NULL;

                    num = dice();
                    one.pos += num;
                    if (one.pos > 35)
                    {
                        one.pos -= 36;
                        one.money += 200;
                    }
                    one.x = map[one.pos].x;
                    one.y = map[one.pos].y;
                    currdice = dicee[num - 1];
                    change_rect(&pl1, one.x, one.y, SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27);
                    player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                    tur1 = true;
                }
                else if (map[one.pos].key == 1 && turn1 && tur1)
                {
                    massege = wkey;
                    if (e.key.keysym.sym == SDLK_y && SDL_KEYUP == e.type)
                    {
                        if (1000 > one.money)
                        {
                            massege = dmoney;
                            tur1 = false;
                            turn1 = false;
                            turn2 = true;
                        }
                        else
                        {
                            one.opened_chest++;
                            one.money -= 1000;
                            player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                            massege = NULL;
                            map[key_int].key = false;
                            key_int = keygen();
                            map[key_int].key = true;
                            change_rect(&key_gen, map[key_int].x - SCREEN_HEIGHT / 32, map[key_int].y - SCREEN_HEIGHT / 72, SCREEN_HEIGHT / 16, SCREEN_HEIGHT / 36);
                            player_1_info_chests = chests[one.opened_chest];
                            if (one.opened_chest == 4)
                                winn = true;
                            tur1 = false;
                            turn1 = false;
                            turn2 = true;
                        }
                    }
                    else if (e.key.keysym.sym == SDLK_n && SDL_KEYUP == e.type)
                    {
                        massege = NULL;
                        tur1 = false;
                        turn1 = false;
                        turn2 = true;
                    } 
                }
                else if (map[one.pos].cost != 0 && map[one.pos].index_p == 0 && turn1 && tur1)
                {
                    massege = want_you;
                    if (e.key.keysym.sym == SDLK_y && SDL_KEYUP == e.type)
                    {
                        if (map[one.pos].cost > one.money)
                        {
                            massege = dmoney;
                            tur1 = false;
                            turn1 = false;
                            turn2 = true;
                        }
                        else
                        {
                            map[one.pos].index_p = 1;
                            one.money -= map[one.pos].cost;
                            player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                            massege = NULL;
                            tur1 = false;
                            turn1 = false;
                            turn2 = true;
                        }
                    }
                    else if (e.key.keysym.sym == SDLK_n && SDL_KEYUP == e.type)
                    {
                        massege = NULL;
                        tur1 = false;
                        turn1 = false;
                        turn2 = true;
                    }
                }
                else if (map[one.pos].cost != 0 && map[one.pos].index_p == 2 && turn1 && tur1)
                {
                    if (one.money < map[one.pos].cost / 2)
                    {
                        two.money += one.money;
                        one.money = 0;
                        tur1 = false;
                        turn1 = false;
                        turn2 = true;
                        player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                        player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                    }
                    else{
                        two.money += map[one.pos].cost / 2;
                        one.money -= map[one.pos].cost / 2;
                        tur1 = false;
                        turn1 = false;
                        turn2 = true;
                        player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                        player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                    }
                }
                else if (map[one.pos].cost != 0 && map[one.pos].index_p == 3 && turn1 && tur1)
                {
                    if (one.money < map[one.pos].cost / 2)
                    {
                        three.money += one.money;
                        one.money = 0;
                        tur1 = false;
                        turn1 = false;
                        turn2 = true;
                        player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                        player_3_info_balance = num_to_texture(font_dited, rend, three.money, &black);
                    }
                    else{
                        three.money += map[one.pos].cost / 2;
                        one.money -= map[one.pos].cost / 2;
                        tur1 = false;
                        turn1 = false;
                        turn2 = true;
                        player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                        player_3_info_balance = num_to_texture(font_dited, rend, three.money, &black);
                    }
                }
                else if ((one.pos == 3 || one.pos == 29) && tur1 && turn1)
                {
                    if (one.money < 150)
                    {
                        one.money = 0;
                        tur1 = false;
                        turn1 = false;
                        turn2 = true;
                        player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                    }
                    else{
                        one.money -= 150;
                        tur1 = false;
                        turn1 = false;
                        turn2 = true;
                        player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                    }
                }
                else if ((one.pos == 12 || one.pos == 20 || one.pos == 33) && turn1 && tur1)
                {
                    one.money += rand_num();
                    tur1 = false;
                    turn1 = false;
                    turn2 = true;
                    player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                }
                else if (one.pos == 9 && turn1 && tur1)
                {
                    one.pos = 27;
                    one.skip = 4;
                    change_rect(&pl1, map[one.pos].x, map[one.pos].y, 20, 20);
                    tur1 = false;
                    turn1 = false;
                    turn2 = true;
                }
                else if (one.pos == 27 && turn1 && tur1)
                {
                    one.skip = 4;
                    tur1 = false;
                    turn1 = false;
                    turn2 = true;
                }
                else if (one.pos == 18 && turn1 && tur1)
                {
                    one.pos += 8;
                    one.money += 100;
                    tur1 = false;
                    turn1 = false;
                    turn2 = true;
                    player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                    change_rect(&pl1, map[one.pos].x, map[one.pos].y, 20, 20);

                }
                else if ((one.pos == 7 || one.pos == 16 || one.pos == 24) && turn1 && tur1 && e.key.keysym.sym == SDLK_RETURN && SDL_KEYUP == e.type)
                {
                    int cn = dice();
                    if (cn == 1)
                    {
                        one.money += 50;
                        currchan = chances[0];
                    }
                    else if (cn == 2)
                    {
                        one.money += 100;
                        currchan = chances[1];
                    }
                    else if (cn == 3)
                    {
                        one.money += 150;
                        currchan = chances[2];
                    }
                    else if (cn == 4)
                    {
                        one.money -= 50;
                        if (one.money < 0)
                            one.money = 0;
                        currchan = chances[3];
                    }
                    else if (cn == 5)
                    {
                        one.money -= 100;
                        if (one.money < 0)
                            one.money = 0;
                        currchan = chances[4];
                    }
                    else if (cn == 6)
                    {
                        one.money -= 150;
                        if (one.money < 0)
                            one.money = 0;
                        currchan = chances[5];
                    }
                    player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                    tur1 = false;
                    turn1 = false;
                    turn2 = true;
                }
                else if ((one.pos == 14 || one.pos == 22) && tur1 && turn1)
                {
                    if (one.pos == 14)
                    {
                        for (int i = 0; i < 36; i++)
                        {
                            if (map[i].index_p == 1)
                            {
                                if (fifty())
                                {
                                    map[i].index_p = 0;
                                    break;
                                }
                                else
                                    continue;
                            }
                        }
                        
                    }
                    else if (one.pos == 22)
                    {
                        for (int i = 0; i < 36; i++)
                        {
                            if (map[i].index_p == 1)
                                map[i].index_p = 0;
                        }
                    }
                    tur1 = false;
                    turn1 = false;
                    turn2 = true;
                }
                else if (one.pos == 0 && turn1 && tur1)
                {
                    tur1 = false;
                    turn1 = false;
                    turn2 = true;
                }
                else if (map[one.pos].cost != 0 && map[one.pos].index_p == 1 && turn1 && tur1)
                {
                    tur1 = false;
                    turn1 = false;
                    turn2 = true;
                }
                else if (e.key.keysym.sym == SDLK_RETURN && SDL_KEYUP == e.type && two.skip != 0 && turn2 && !tur2)
                {
                    massege = NULL;
                    currchan = NULL;
                    two.skip--;
                    turn2 = false;
                    tur2 = false;
                    turn3 = true;
                }
                else if(e.key.keysym.sym == SDLK_RETURN && SDL_KEYUP == e.type && turn2 && !tur2)
                {
                    massege = NULL;
                    currchan = NULL;
                    num = dice();
                    two.pos += num;
                    if (two.pos > 35)
                    {
                        two.pos -= 36;
                        two.money += 200;
                    }
                    two.x = map[two.pos].x;
                    two.y = map[two.pos].y;
                    currdice = dicee[num - 1];
                    change_rect(&pl2, two.x - SCREEN_HEIGHT / 27, two.y, SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27);
                    player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                    tur2 = true;
                }
                else if (map[two.pos].key == 1 && turn2 && tur2)
                {
                    massege = wkey;
                    if (e.key.keysym.sym == SDLK_y && SDL_KEYUP == e.type)
                    {
                        if (1000 > two.money)
                        {
                            massege = dmoney;
                            tur2 = false;
                            turn2 = false;
                            turn3 = true;
                        }
                        else
                        {
                            two.opened_chest++;
                            two.money -= 1000;
                            player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                            massege = NULL;
                            map[key_int].key = false;
                            key_int = keygen();
                            map[key_int].key = true;
                            change_rect(&key_gen, map[key_int].x - SCREEN_HEIGHT / 32, map[key_int].y - SCREEN_HEIGHT / 72, SCREEN_HEIGHT / 16, SCREEN_HEIGHT / 36);
                            player_2_info_chests = chests[two.opened_chest];
                            if (two.opened_chest == 4)
                                winn = true;
                            tur2 = false;
                            turn2 = false;
                            turn3 = true;
                        }
                    }
                    else if (e.key.keysym.sym == SDLK_n && SDL_KEYUP == e.type)
                    {
                        massege = NULL;
                        tur2 = false;
                        turn2 = false;
                        turn3 = true;
                    }
                }
                else if (map[two.pos].cost != 0 && map[two.pos].index_p == 0 && turn2 && tur2)
                {
                    massege = want_you;
                    if (e.key.keysym.sym == SDLK_y && SDL_KEYUP == e.type)
                    {
                        if (map[two.pos].cost > two.money)
                        {
                            massege = dmoney;
                            tur2 = false;
                            turn2 = false;
                            turn3 = true;
                        }
                        else
                        {
                            map[two.pos].index_p = 2;
                            two.money -= map[two.pos].cost;
                            player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                            massege = NULL;
                            tur2 = false;
                            turn2 = false;
                            turn3 = true;
                        }
                    }
                    else if (e.key.keysym.sym == SDLK_n && SDL_KEYUP == e.type)
                    {
                        massege = NULL;
                        tur2 = false;
                        turn2 = false;
                        turn3 = true;
                    }
                }
                else if (map[two.pos].cost != 0 && map[two.pos].index_p == 1 && turn2 && tur2)
                {
                    if (two.money < map[two.pos].cost / 2)
                    {
                        one.money += two.money;
                        two.money = 0;
                        tur2 = false;
                        turn2 = false;
                        turn3 = true;
                        player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                        player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                    }
                    else{
                        one.money += map[two.pos].cost / 2;
                        two.money -= map[two.pos].cost / 2;
                        tur2 = false;
                        turn2 = false;
                        turn3 = true;
                        player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                        player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                    }
                }
                else if (map[two.pos].cost != 0 && map[two.pos].index_p == 1 && turn2 && tur2)
                {
                    if (two.money < map[two.pos].cost / 2)
                    {
                        three.money += two.money;
                        two.money = 0;
                        tur2 = false;
                        turn2 = false;
                        turn3 = true;
                        player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                        player_3_info_balance = num_to_texture(font_dited, rend, three.money, &black);
                    }
                    else{
                        three.money += map[two.pos].cost / 2;
                        two.money -= map[two.pos].cost / 2;
                        tur2 = false;
                        turn2 = false;
                        turn3 = true;
                        player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                        player_3_info_balance = num_to_texture(font_dited, rend, three.money, &black);
                    }
                }
                else if ((two.pos == 3 || two.pos == 29) && tur2 && turn2)
                {
                    if (two.money < 150)
                    {
                        two.money = 0;
                        tur2 = false;
                        turn2 = false;
                        turn3 = true;
                        player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                    }
                    else{
                        two.money -= 150;
                        tur2 = false;
                        turn2 = false;
                        turn3 = true;
                        player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                    }
                }
                else if ((two.pos == 12 || two.pos == 20 || two.pos == 33) && turn2 && tur2)
                {
                    two.money += rand_num();
                    tur2 = false;
                    turn2 = false;
                    turn3 = true;
                    player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                }
                else if (two.pos == 9 && turn2 && tur2)
                {
                    two.pos = 27;
                    two.skip = 4;
                    change_rect(&pl2, map[two.pos].x - 20, map[two.pos].y, 20, 20);
                    tur2 = false;
                    turn2 = false;
                    turn3 = true;
                }
                else if (two.pos == 27 && turn2 && tur2)
                {
                    two.skip = 4;
                    tur2 = false;
                    turn2 = false;
                    turn3 = true;
                }
                else if (two.pos == 18 && turn2 && tur2)
                {
                    two.pos += 8;
                    two.money += 100;
                    tur2 = false;
                    turn2 = false;
                    turn3 = true;
                    player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                    change_rect(&pl2, map[two.pos].x - 20, map[two.pos].y, 20, 20);

                }
                else if ((two.pos == 7 || two.pos == 16 || two.pos == 24) && turn2 && tur2 && e.key.keysym.sym == SDLK_RETURN && SDL_KEYUP == e.type )
                {
                    int cn = dice();
                    if (cn == 1)
                    {
                        two.money += 50;
                        currchan = chances[0];
                    }
                    else if (cn == 2)
                    {
                        two.money += 100;
                        currchan = chances[1];
                    }
                    else if (cn == 3)
                    {
                        two.money += 150;
                        currchan = chances[2];
                    }
                    else if (cn == 4)
                    {
                        two.money -= 50;
                        if (two.money < 0)
                            two.money = 0;
                        currchan = chances[3];
                    }
                    else if (cn == 5)
                    {
                        two.money -= 100;
                        if (two.money < 0)
                            two.money = 0;
                        currchan = chances[4];
                    }
                    else if (cn == 6)
                    {
                        two.money -= 150;
                        if (two.money < 0)
                            two.money = 0;
                        currchan = chances[5];
                    }
                    player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                    tur2 = false;
                    turn2 = false;
                    turn3 = true;
                }
                else if ((two.pos == 14 || two.pos == 22) && tur2 && turn2)
                {
                    if (two.pos == 14)
                    {
                        for (int i = 0; i < 36; i++)
                        {
                            if (map[i].index_p == 2)
                            {
                                if (fifty())
                                {
                                    map[i].index_p = 0;
                                    break;
                                }
                                else
                                    continue;
                            }
                        }
                        
                    }
                    else if (two.pos == 22)
                    {
                        for (int i = 0; i < 36; i++)
                        {
                            if (map[i].index_p == 2)
                                map[i].index_p = 0;
                        }
                    }
                    tur2 = false;
                    turn2 = false;
                    turn3 = true;
                }
                else if (two.pos == 0 && tur2 && turn2)
                {
                    tur2 = false;
                    turn2 = false;
                    turn3 = true;
                }
                else if (map[two.pos].cost != 0 && map[two.pos].index_p == 2 && turn2 && tur2)
                {
                    tur2 = false;
                    turn2 = false;
                    turn3 = true;
                }
                if (e.key.keysym.sym == SDLK_RETURN && SDL_KEYUP == e.type && three.skip != 0 && turn3 && !tur3)
                {
                    massege = NULL;
                    currchan = NULL;
                    three.skip--;
                    turn3 = false;
                    tur3 = false;
                    turn1 = true;
                }
                else if(e.key.keysym.sym == SDLK_RETURN && SDL_KEYUP == e.type && turn3 && !tur3)
                {
                    massege = NULL;
                    currchan = NULL;

                    num = dice();
                    three.pos += num;
                    if (three.pos > 35)
                    {
                        three.pos -= 36;
                        three.money += 200;
                    }
                    three.x = map[three.pos].x;
                    three.y = map[three.pos].y;
                    currdice = dicee[num - 1];
                    change_rect(&pl3, three.x - SCREEN_HEIGHT / 27, three.y - SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27);
                    player_3_info_balance = num_to_texture(font_dited, rend, three.money, &black);
                    tur3 = true;
                }
                else if (map[three.pos].key == 1 && turn3 && tur3)
                {
                    massege = wkey;
                    if (e.key.keysym.sym == SDLK_y && SDL_KEYUP == e.type)
                    {
                        if (1000 > three.money)
                        {
                            massege = dmoney;
                            tur3 = false;
                            turn3 = false;
                            turn1 = true;
                        }
                        else
                        {
                            three.opened_chest++;
                            three.money -= 1000;
                            player_3_info_balance = num_to_texture(font_dited, rend, three.money, &black);
                            massege = NULL;
                            map[key_int].key = false;
                            key_int = keygen();
                            map[key_int].key = true;
                            change_rect(&key_gen, map[key_int].x - SCREEN_HEIGHT / 32, map[key_int].y - SCREEN_HEIGHT / 72, SCREEN_HEIGHT / 16, SCREEN_HEIGHT / 36);
                            player_3_info_chests = chests[three.opened_chest];
                            if (three.opened_chest == 4)
                                winn = true;
                            tur3 = false;
                            turn3 = false;
                            turn1 = true;
                        }
                    }
                    else if (e.key.keysym.sym == SDLK_n && SDL_KEYUP == e.type)
                    {
                        massege = NULL;
                        tur3 = false;
                        turn3 = false;
                        turn1 = true;
                    }
                }
                else if (map[three.pos].cost != 0 && map[three.pos].index_p == 0 && turn3 && tur3)
                {
                    massege = want_you;
                    if (e.key.keysym.sym == SDLK_y && SDL_KEYUP == e.type)
                    {
                        if (map[three.pos].cost > three.money)
                        {
                            massege = dmoney;
                            tur3 = false;
                            turn3 = false;
                            turn1 = true;
                        }
                        else
                        {
                            map[three.pos].index_p = 3;
                            three.money -= map[three.pos].cost;
                            player_3_info_balance = num_to_texture(font_dited, rend, three.money, &black);
                            massege = NULL;
                            tur3 = false;
                            turn3 = false;
                            turn1 = true;
                        }
                    }
                    else if (e.key.keysym.sym == SDLK_n && SDL_KEYUP == e.type)
                    {
                        massege = NULL;
                        tur3 = false;
                        turn3 = false;
                        turn1 = true;
                    }
                }
                else if (map[three.pos].cost != 0 && map[three.pos].index_p == 2 && turn3 && tur3)
                {
                    if (three.money < map[three.pos].cost / 2)
                    {
                        two.money += three.money;
                        three.money = 0;
                        tur3 = false;
                        turn3 = false;
                        turn1 = true;
                        player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                        player_3_info_balance = num_to_texture(font_dited, rend, three.money, &black);
                    }
                    else{
                        two.money += map[three.pos].cost / 2;
                        three.money -= map[three.pos].cost / 2;
                        tur3 = false;
                        turn3 = false;
                        turn1 = true;
                        player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                        player_3_info_balance = num_to_texture(font_dited, rend, three.money, &black);
                    }
                }
                else if (map[one.pos].cost != 0 && map[one.pos].index_p == 1 && turn3 && tur3)
                {
                    if (three.money < map[three.pos].cost / 2)
                    {
                        one.money += three.money;
                        three.money = 0;
                        tur3 = false;
                        turn3 = false;
                        turn1 = true;
                        player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                        player_3_info_balance = num_to_texture(font_dited, rend, three.money, &black);
                    }
                    else{
                        one.money += map[one.pos].cost / 2;
                        three.money -= map[one.pos].cost / 2;
                        tur3 = false;
                        turn3 = false;
                        turn1 = true;
                        player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                        player_3_info_balance = num_to_texture(font_dited, rend, three.money, &black);
                    }
                }
                else if ((three.pos == 3 || three.pos == 29) && tur3 && turn3)
                {
                    if (three.money < 150)
                    {
                        three.money = 0;
                        tur3 = false;
                        turn3 = false;
                        turn1 = true;
                        player_3_info_balance = num_to_texture(font_dited, rend, three.money, &black);
                    }
                    else{
                        three.money -= 150;
                        tur3 = false;
                        turn3 = false;
                        turn1 = true;
                        player_3_info_balance = num_to_texture(font_dited, rend, three.money, &black);
                    }
                }
                else if ((three.pos == 12 || three.pos == 20 || three.pos == 33) && turn3 && tur3)
                {
                    three.money += rand_num();
                    tur3 = false;
                    turn3 = false;
                    turn1 = true;
                    player_3_info_balance = num_to_texture(font_dited, rend, three.money, &black);
                }
                else if (three.pos == 9 && turn3 && tur3)
                {
                    three.pos = 27;
                    three.skip = 4;
                    change_rect(&pl3, map[three.pos].x, map[three.pos].y, 20, 20);
                    tur3 = false;
                    turn3 = false;
                    turn1 = true;
                }
                else if (three.pos == 27 && turn3 && tur3)
                {
                    three.skip = 4;
                    tur3 = false;
                    turn3 = false;
                    turn1 = true;
                }
                else if (three.pos == 18 && turn3 && tur3)
                {
                    three.pos += 8;
                    three.money += 100;
                    tur3 = false;
                    turn3 = false;
                    turn1 = true;
                    player_3_info_balance = num_to_texture(font_dited, rend, three.money, &black);
                    change_rect(&pl1, map[three.pos].x, map[three.pos].y, 20, 20);

                }
                else if ((three.pos == 7 || three.pos == 16 || three.pos == 24) && turn3 && tur3 && e.key.keysym.sym == SDLK_RETURN && SDL_KEYUP == e.type)
                {
                    int cn = dice();
                    if (cn == 1)
                    {
                        three.money += 50;
                        currchan = chances[0];
                    }
                    else if (cn == 2)
                    {
                        three.money += 100;
                        currchan = chances[1];
                    }
                    else if (cn == 3)
                    {
                        three.money += 150;
                        currchan = chances[2];
                    }
                    else if (cn == 4)
                    {
                        three.money -= 50;
                        if (three.money < 0)
                            three.money = 0;
                        currchan = chances[3];
                    }
                    else if (cn == 5)
                    {
                        three.money -= 100;
                        if (three.money < 0)
                            three.money = 0;
                        currchan = chances[4];
                    }
                    else if (cn == 6)
                    {
                        three.money -= 150;
                        if (three.money < 0)
                            three.money = 0;
                        currchan = chances[5];
                    }
                    player_3_info_balance = num_to_texture(font_dited, rend, three.money, &black);
                    tur3 = false;
                    turn3 = false;
                    turn1 = true;
                }
                else if ((three.pos == 14 || three.pos == 22) && tur3 && turn3)
                {
                    if (three.pos == 14)
                    {
                        for (int i = 0; i < 36; i++)
                        {
                            if (map[i].index_p == 3)
                            {
                                if (fifty())
                                {
                                    map[i].index_p = 0;
                                    break;
                                }
                                else
                                    continue;
                            }
                        }
                        
                    }
                    else if (three.pos == 22)
                    {
                        for (int i = 0; i < 36; i++)
                        {
                            if (map[i].index_p == 3)
                                map[i].index_p = 0;
                        }
                    }
                    tur3 = false;
                    turn3 = false;
                    turn1 = true;
                }
                else if (three.pos == 0 && turn3 && tur3)
                {
                    tur3 = false;
                    turn3 = false;
                    turn1 = true;
                }
                else if (map[three.pos].cost != 0 && map[three.pos].index_p == 3 && turn3 && tur3)
                {
                    tur3 = false;
                    turn3 = false;
                    turn1 = true;
                }
            }
            else if (game_is_started && !menu_is_open && players == 4) {
                if (e.key.keysym.sym == SDLK_RETURN && SDL_KEYUP == e.type && one.skip != 0 && turn1 && !tur1)
                {
                    massege = NULL;
                    currchan = NULL;
                    one.skip--;
                    turn1 = false;
                    tur1 = false;
                    turn2 = true;
                }
                else if(e.key.keysym.sym == SDLK_RETURN && SDL_KEYUP == e.type && turn1 && !tur1)
                {
                    massege = NULL;
                    currchan = NULL;

                    num = dice();
                    one.pos += num;
                    if (one.pos > 35)
                    {
                        one.pos -= 36;
                        one.money += 200;
                    }
                    one.x = map[one.pos].x;
                    one.y = map[one.pos].y;
                    currdice = dicee[num - 1];
                    change_rect(&pl1, one.x, one.y, SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27);
                    player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                    tur1 = true;
                }
                else if (map[one.pos].key == 1 && turn1 && tur1)
                {
                    massege = wkey;
                    if (e.key.keysym.sym == SDLK_y && SDL_KEYUP == e.type)
                    {
                        if (1000 > one.money)
                        {
                            massege = dmoney;
                            tur1 = false;
                            turn1 = false;
                            turn2 = true;
                        }
                        else
                        {
                            one.opened_chest++;
                            one.money -= 1000;
                            player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                            massege = NULL;
                            map[key_int].key = false;
                            key_int = keygen();
                            map[key_int].key = true;
                            change_rect(&key_gen, map[key_int].x - SCREEN_HEIGHT / 32, map[key_int].y - SCREEN_HEIGHT / 72, SCREEN_HEIGHT / 16, SCREEN_HEIGHT / 36);
                            player_1_info_chests = chests[one.opened_chest];
                            if (one.opened_chest == 4)
                                winn = true;
                            tur1 = false;
                            turn1 = false;
                            turn2 = true;
                        }
                    }
                    else if (e.key.keysym.sym == SDLK_n && SDL_KEYUP == e.type)
                    {
                        massege = NULL;
                        tur1 = false;
                        turn1 = false;
                        turn2 = true;
                    } 
                }
                else if (map[one.pos].cost != 0 && map[one.pos].index_p == 0 && turn1 && tur1)
                {
                    massege = want_you;
                    if (e.key.keysym.sym == SDLK_y && SDL_KEYUP == e.type)
                    {
                        if (map[one.pos].cost > one.money)
                        {
                            massege = dmoney;
                            tur1 = false;
                            turn1 = false;
                            turn2 = true;
                        }
                        else
                        {
                            map[one.pos].index_p = 1;
                            one.money -= map[one.pos].cost;
                            player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                            massege = NULL;
                            tur1 = false;
                            turn1 = false;
                            turn2 = true;
                        }
                    }
                    else if (e.key.keysym.sym == SDLK_n && SDL_KEYUP == e.type)
                    {
                        massege = NULL;
                        tur1 = false;
                        turn1 = false;
                        turn2 = true;
                    }
                }
                else if (map[one.pos].cost != 0 && map[one.pos].index_p == 2 && turn1 && tur1)
                {
                    if (one.money < map[one.pos].cost / 2)
                    {
                        two.money += one.money;
                        one.money = 0;
                        tur1 = false;
                        turn1 = false;
                        turn2 = true;
                        player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                        player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                    }
                    else{
                        two.money += map[one.pos].cost / 2;
                        one.money -= map[one.pos].cost / 2;
                        tur1 = false;
                        turn1 = false;
                        turn2 = true;
                        player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                        player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                    }
                }
                else if (map[one.pos].cost != 0 && map[one.pos].index_p == 3 && turn1 && tur1)
                {
                    if (one.money < map[one.pos].cost / 2)
                    {
                        three.money += one.money;
                        one.money = 0;
                        tur1 = false;
                        turn1 = false;
                        turn2 = true;
                        player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                        player_3_info_balance = num_to_texture(font_dited, rend, three.money, &black);
                    }
                    else{
                        three.money += map[one.pos].cost / 2;
                        one.money -= map[one.pos].cost / 2;
                        tur1 = false;
                        turn1 = false;
                        turn2 = true;
                        player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                        player_3_info_balance = num_to_texture(font_dited, rend, three.money, &black);
                    }
                }
                else if (map[one.pos].cost != 0 && map[one.pos].index_p == 4 && turn1 && tur1)
                {
                    if (one.money < map[one.pos].cost / 2)
                    {
                        four.money += one.money;
                        one.money = 0;
                        tur1 = false;
                        turn1 = false;
                        turn2 = true;
                        player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                        player_4_info_balance = num_to_texture(font_dited, rend, four.money, &black);
                    }
                    else{
                        four.money += map[one.pos].cost / 2;
                        one.money -= map[one.pos].cost / 2;
                        tur1 = false;
                        turn1 = false;
                        turn2 = true;
                        player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                        player_4_info_balance = num_to_texture(font_dited, rend, four.money, &black);
                    }
                }
                else if ((one.pos == 3 || one.pos == 29) && tur1 && turn1)
                {
                    if (one.money < 150)
                    {
                        one.money = 0;
                        tur1 = false;
                        turn1 = false;
                        turn2 = true;
                        player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                    }
                    else{
                        one.money -= 150;
                        tur1 = false;
                        turn1 = false;
                        turn2 = true;
                        player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                    }
                }
                else if ((one.pos == 12 || one.pos == 20 || one.pos == 33) && turn1 && tur1)
                {
                    one.money += rand_num();
                    tur1 = false;
                    turn1 = false;
                    turn2 = true;
                    player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                }
                else if (one.pos == 9 && turn1 && tur1)
                {
                    one.pos = 27;
                    one.skip = 4;
                    change_rect(&pl1, map[one.pos].x, map[one.pos].y, 20, 20);
                    tur1 = false;
                    turn1 = false;
                    turn2 = true;
                }
                else if (one.pos == 27 && turn1 && tur1)
                {
                    one.skip = 4;
                    tur1 = false;
                    turn1 = false;
                    turn2 = true;
                }
                else if (one.pos == 18 && turn1 && tur1)
                {
                    one.pos += 8;
                    one.money += 100;
                    tur1 = false;
                    turn1 = false;
                    turn2 = true;
                    player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                    change_rect(&pl1, map[one.pos].x, map[one.pos].y, 20, 20);

                }
                else if ((one.pos == 7 || one.pos == 16 || one.pos == 24) && turn1 && tur1 && e.key.keysym.sym == SDLK_RETURN && SDL_KEYUP == e.type)
                {
                    int cn = dice();
                    if (cn == 1)
                    {
                        one.money += 50;
                        currchan = chances[0];
                    }
                    else if (cn == 2)
                    {
                        one.money += 100;
                        currchan = chances[1];
                    }
                    else if (cn == 3)
                    {
                        one.money += 150;
                        currchan = chances[2];
                    }
                    else if (cn == 4)
                    {
                        one.money -= 50;
                        if (one.money < 0)
                            one.money = 0;
                        currchan = chances[3];
                    }
                    else if (cn == 5)
                    {
                        one.money -= 100;
                        if (one.money < 0)
                            one.money = 0;
                        currchan = chances[4];
                    }
                    else if (cn == 6)
                    {
                        one.money -= 150;
                        if (one.money < 0)
                            one.money = 0;
                        currchan = chances[5];
                    }
                    player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                    tur1 = false;
                    turn1 = false;
                    turn2 = true;
                }
                else if ((one.pos == 14 || one.pos == 22) && tur1 && turn1)
                {
                    if (one.pos == 14)
                    {
                        for (int i = 0; i < 36; i++)
                        {
                            if (map[i].index_p == 1)
                            {
                                if (fifty())
                                {
                                    map[i].index_p = 0;
                                    break;
                                }
                                else
                                    continue;
                            }
                        }
                        
                    }
                    else if (one.pos == 22)
                    {
                        for (int i = 0; i < 36; i++)
                        {
                            if (map[i].index_p == 1)
                                map[i].index_p = 0;
                        }
                    }
                    tur1 = false;
                    turn1 = false;
                    turn2 = true;
                }
                else if (one.pos == 0 && turn1 && tur1)
                {
                    tur1 = false;
                    turn1 = false;
                    turn2 = true;
                }
                else if (map[one.pos].cost != 0 && map[one.pos].index_p == 1 && turn1 && tur1)
                {
                    tur1 = false;
                    turn1 = false;
                    turn2 = true;
                }
                else if (e.key.keysym.sym == SDLK_RETURN && SDL_KEYUP == e.type && two.skip != 0 && turn2 && !tur2)
                {
                    massege = NULL;
                    currchan = NULL;
                    two.skip--;
                    turn2 = false;
                    tur2 = false;
                    turn3 = true;
                }
                else if(e.key.keysym.sym == SDLK_RETURN && SDL_KEYUP == e.type && turn2 && !tur2)
                {
                    massege = NULL;
                    currchan = NULL;
                    num = dice();
                    two.pos += num;
                    if (two.pos > 35)
                    {
                        two.pos -= 36;
                        two.money += 200;
                    }
                    two.x = map[two.pos].x;
                    two.y = map[two.pos].y;
                    currdice = dicee[num - 1];
                    change_rect(&pl2, two.x - SCREEN_HEIGHT / 27, two.y, SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27);
                    player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                    tur2 = true;
                }
                else if (map[two.pos].key == 1 && turn2 && tur2)
                {
                    massege = wkey;
                    if (e.key.keysym.sym == SDLK_y && SDL_KEYUP == e.type)
                    {
                        if (1000 > two.money)
                        {
                            massege = dmoney;
                            tur2 = false;
                            turn2 = false;
                            turn3 = true;
                        }
                        else
                        {
                            two.opened_chest++;
                            two.money -= 1000;
                            player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                            massege = NULL;
                            map[key_int].key = false;
                            key_int = keygen();
                            map[key_int].key = true;
                            change_rect(&key_gen, map[key_int].x - SCREEN_HEIGHT / 32, map[key_int].y - SCREEN_HEIGHT / 72, SCREEN_HEIGHT / 16, SCREEN_HEIGHT / 36);
                            player_2_info_chests = chests[two.opened_chest];
                            if (two.opened_chest == 4)
                                winn = true;
                            tur2 = false;
                            turn2 = false;
                            turn3 = true;
                        }
                    }
                    else if (e.key.keysym.sym == SDLK_n && SDL_KEYUP == e.type)
                    {
                        massege = NULL;
                        tur2 = false;
                        turn2 = false;
                        turn3 = true;
                    }
                }
                else if (map[two.pos].cost != 0 && map[two.pos].index_p == 0 && turn2 && tur2)
                {
                    massege = want_you;
                    if (e.key.keysym.sym == SDLK_y && SDL_KEYUP == e.type)
                    {
                        if (map[two.pos].cost > two.money)
                        {
                            massege = dmoney;
                            tur2 = false;
                            turn2 = false;
                            turn3 = true;
                        }
                        else
                        {
                            map[two.pos].index_p = 2;
                            two.money -= map[two.pos].cost;
                            player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                            massege = NULL;
                            tur2 = false;
                            turn2 = false;
                            turn3 = true;
                        }
                    }
                    else if (e.key.keysym.sym == SDLK_n && SDL_KEYUP == e.type)
                    {
                        massege = NULL;
                        tur2 = false;
                        turn2 = false;
                        turn3 = true;
                    }
                }
                else if (map[two.pos].cost != 0 && map[two.pos].index_p == 1 && turn2 && tur2)
                {
                    if (two.money < map[two.pos].cost / 2)
                    {
                        one.money += two.money;
                        two.money = 0;
                        tur2 = false;
                        turn2 = false;
                        turn3 = true;
                        player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                        player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                    }
                    else{
                        one.money += map[two.pos].cost / 2;
                        two.money -= map[two.pos].cost / 2;
                        tur2 = false;
                        turn2 = false;
                        turn3 = true;
                        player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                        player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                    }
                }
                else if (map[two.pos].cost != 0 && map[two.pos].index_p == 3 && turn2 && tur2)
                {
                    if (two.money < map[two.pos].cost / 2)
                    {
                        three.money += two.money;
                        two.money = 0;
                        tur2 = false;
                        turn2 = false;
                        turn3 = true;
                        player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                        player_3_info_balance = num_to_texture(font_dited, rend, three.money, &black);
                    }
                    else{
                        three.money += map[two.pos].cost / 2;
                        two.money -= map[two.pos].cost / 2;
                        tur2 = false;
                        turn2 = false;
                        turn3 = true;
                        player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                        player_3_info_balance = num_to_texture(font_dited, rend, three.money, &black);
                    }
                }
                else if (map[two.pos].cost != 0 && map[two.pos].index_p == 4 && turn2 && tur2)
                {
                    if (two.money < map[two.pos].cost / 2)
                    {
                        four.money += two.money;
                        two.money = 0;
                        tur2 = false;
                        turn2 = false;
                        turn3 = true;
                        player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                        player_4_info_balance = num_to_texture(font_dited, rend, four.money, &black);
                    }
                    else{
                        four.money += map[two.pos].cost / 2;
                        two.money -= map[two.pos].cost / 2;
                        tur2 = false;
                        turn2 = false;
                        turn3 = true;
                        player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                        player_4_info_balance = num_to_texture(font_dited, rend, four.money, &black);
                    }
                }
                else if ((two.pos == 3 || two.pos == 29) && tur2 && turn2)
                {
                    if (two.money < 150)
                    {
                        two.money = 0;
                        tur2 = false;
                        turn2 = false;
                        turn3 = true;
                        player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                    }
                    else{
                        two.money -= 150;
                        tur2 = false;
                        turn2 = false;
                        turn3 = true;
                        player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                    }
                }
                else if ((two.pos == 12 || two.pos == 20 || two.pos == 33) && turn2 && tur2)
                {
                    two.money += rand_num();
                    tur2 = false;
                    turn2 = false;
                    turn3 = true;
                    player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                }
                else if (two.pos == 9 && turn2 && tur2)
                {
                    two.pos = 27;
                    two.skip = 4;
                    change_rect(&pl2, map[two.pos].x - 20, map[two.pos].y, 20, 20);
                    tur2 = false;
                    turn2 = false;
                    turn3 = true;
                }
                else if (two.pos == 27 && turn2 && tur2)
                {
                    two.skip = 4;
                    tur2 = false;
                    turn2 = false;
                    turn3 = true;
                }
                else if (two.pos == 18 && turn2 && tur2)
                {
                    two.pos += 8;
                    two.money += 100;
                    tur2 = false;
                    turn2 = false;
                    turn3 = true;
                    player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                    change_rect(&pl2, map[two.pos].x - 20, map[two.pos].y, 20, 20);

                }
                else if ((two.pos == 7 || two.pos == 16 || two.pos == 24) && turn2 && tur2 && e.key.keysym.sym == SDLK_RETURN && SDL_KEYUP == e.type )
                {
                    int cn = dice();
                    if (cn == 1)
                    {
                        two.money += 50;
                        currchan = chances[0];
                    }
                    else if (cn == 2)
                    {
                        two.money += 100;
                        currchan = chances[1];
                    }
                    else if (cn == 3)
                    {
                        two.money += 150;
                        currchan = chances[2];
                    }
                    else if (cn == 4)
                    {
                        two.money -= 50;
                        if (two.money < 0)
                            two.money = 0;
                        currchan = chances[3];
                    }
                    else if (cn == 5)
                    {
                        two.money -= 100;
                        if (two.money < 0)
                            two.money = 0;
                        currchan = chances[4];
                    }
                    else if (cn == 6)
                    {
                        two.money -= 150;
                        if (two.money < 0)
                            two.money = 0;
                        currchan = chances[5];
                    }
                    player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                    tur2 = false;
                    turn2 = false;
                    turn3 = true;
                }
                else if ((two.pos == 14 || two.pos == 22) && tur2 && turn2)
                {
                    if (two.pos == 14)
                    {
                        for (int i = 0; i < 36; i++)
                        {
                            if (map[i].index_p == 2)
                            {
                                if (fifty())
                                {
                                    map[i].index_p = 0;
                                    break;
                                }
                                else
                                    continue;
                            }
                        }
                        
                    }
                    else if (two.pos == 22)
                    {
                        for (int i = 0; i < 36; i++)
                        {
                            if (map[i].index_p == 2)
                                map[i].index_p = 0;
                        }
                    }
                    tur2 = false;
                    turn2 = false;
                    turn3 = true;
                }
                else if (two.pos == 0 && tur2 && turn2)
                {
                    tur2 = false;
                    turn2 = false;
                    turn3 = true;
                }
                else if (map[two.pos].cost != 0 && map[two.pos].index_p == 2 && turn2 && tur2)
                {
                    tur2 = false;
                    turn2 = false;
                    turn3 = true;
                }
                if (e.key.keysym.sym == SDLK_RETURN && SDL_KEYUP == e.type && three.skip != 0 && turn3 && !tur3)
                {
                    massege = NULL;
                    currchan = NULL;
                    three.skip--;
                    turn3 = false;
                    tur3 = false;
                    turn4 = true;
                }
                else if(e.key.keysym.sym == SDLK_RETURN && SDL_KEYUP == e.type && turn3 && !tur3)
                {
                    massege = NULL;
                    currchan = NULL;

                    num = dice();
                    three.pos += num;
                    if (three.pos > 35)
                    {
                        three.pos -= 36;
                        three.money += 200;
                    }
                    three.x = map[three.pos].x;
                    three.y = map[three.pos].y;
                    currdice = dicee[num - 1];
                    change_rect(&pl3, three.x - SCREEN_HEIGHT / 27, three.y - SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27);
                    player_3_info_balance = num_to_texture(font_dited, rend, three.money, &black);
                    tur3 = true;
                }
                else if (map[three.pos].key == 1 && turn3 && tur3)
                {
                    massege = wkey;
                    if (e.key.keysym.sym == SDLK_y && SDL_KEYUP == e.type)
                    {
                        if (1000 > three.money)
                        {
                            massege = dmoney;
                            tur3 = false;
                            turn3 = false;
                            turn4 = true;
                        }
                        else
                        {
                            three.opened_chest++;
                            three.money -= 1000;
                            player_3_info_balance = num_to_texture(font_dited, rend, three.money, &black);
                            massege = NULL;
                            map[key_int].key = false;
                            key_int = keygen();
                            map[key_int].key = true;
                            change_rect(&key_gen, map[key_int].x - SCREEN_HEIGHT / 32, map[key_int].y - SCREEN_HEIGHT / 72, SCREEN_HEIGHT / 16, SCREEN_HEIGHT / 36);
                            player_3_info_chests = chests[three.opened_chest];
                            if (three.opened_chest == 4)
                                winn = true;
                            tur3 = false;
                            turn3 = false;
                            turn4 = true;
                        }
                    }
                    else if (e.key.keysym.sym == SDLK_n && SDL_KEYUP == e.type)
                    {
                        massege = NULL;
                        tur3 = false;
                        turn3 = false;
                        turn4 = true;
                    }
                }
                else if (map[three.pos].cost != 0 && map[three.pos].index_p == 0 && turn3 && tur3)
                {
                    massege = want_you;
                    if (e.key.keysym.sym == SDLK_y && SDL_KEYUP == e.type)
                    {
                        if (map[three.pos].cost > three.money)
                        {
                            massege = dmoney;
                            tur3 = false;
                            turn3 = false;
                            turn4 = true;
                        }
                        else
                        {
                            map[three.pos].index_p = 3;
                            three.money -= map[three.pos].cost;
                            player_3_info_balance = num_to_texture(font_dited, rend, three.money, &black);
                            massege = NULL;
                            tur3 = false;
                            turn3 = false;
                            turn4 = true;
                        }
                    }
                    else if (e.key.keysym.sym == SDLK_n && SDL_KEYUP == e.type)
                    {
                        massege = NULL;
                        tur3 = false;
                        turn3 = false;
                        turn4 = true;
                    }
                }
                else if (map[three.pos].cost != 0 && map[three.pos].index_p == 2 && turn3 && tur3)
                {
                    if (three.money < map[three.pos].cost / 2)
                    {
                        two.money += three.money;
                        three.money = 0;
                        tur3 = false;
                        turn3 = false;
                        turn4 = true;
                        player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                        player_3_info_balance = num_to_texture(font_dited, rend, three.money, &black);
                    }
                    else{
                        two.money += map[three.pos].cost / 2;
                        three.money -= map[three.pos].cost / 2;
                        tur3 = false;
                        turn3 = false;
                        turn4 = true;
                        player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                        player_3_info_balance = num_to_texture(font_dited, rend, three.money, &black);
                    }
                }
                else if (map[one.pos].cost != 0 && map[one.pos].index_p == 1 && turn3 && tur3)
                {
                    if (three.money < map[three.pos].cost / 2)
                    {
                        one.money += three.money;
                        three.money = 0;
                        tur3 = false;
                        turn3 = false;
                        turn4 = true;
                        player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                        player_3_info_balance = num_to_texture(font_dited, rend, three.money, &black);
                    }
                    else{
                        one.money += map[one.pos].cost / 2;
                        three.money -= map[one.pos].cost / 2;
                        tur3 = false;
                        turn3 = false;
                        turn4 = true;
                        player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                        player_3_info_balance = num_to_texture(font_dited, rend, three.money, &black);
                    }
                }
                else if (map[one.pos].cost != 0 && map[one.pos].index_p == 4 && turn3 && tur3)
                {
                    if (three.money < map[three.pos].cost / 2)
                    {
                        four.money += three.money;
                        four.money = 0;
                        tur3 = false;
                        turn3 = false;
                        turn4 = true;
                        player_3_info_balance = num_to_texture(font_dited, rend, three.money, &black);
                        player_4_info_balance = num_to_texture(font_dited, rend, four.money, &black);
                    }
                    else{
                        four.money += map[one.pos].cost / 2;
                        three.money -= map[one.pos].cost / 2;
                        tur3 = false;
                        turn3 = false;
                        turn4 = true;
                        player_3_info_balance = num_to_texture(font_dited, rend, three.money, &black);
                        player_4_info_balance = num_to_texture(font_dited, rend, four.money, &black);
                    }
                }
                else if ((three.pos == 3 || three.pos == 29) && tur3 && turn3)
                {
                    if (three.money < 150)
                    {
                        three.money = 0;
                        tur3 = false;
                        turn3 = false;
                        turn4 = true;
                        player_3_info_balance = num_to_texture(font_dited, rend, three.money, &black);
                    }
                    else{
                        three.money -= 150;
                        tur3 = false;
                        turn3 = false;
                        turn4 = true;
                        player_3_info_balance = num_to_texture(font_dited, rend, three.money, &black);
                    }
                }
                else if ((three.pos == 12 || three.pos == 20 || three.pos == 33) && turn3 && tur3)
                {
                    three.money += rand_num();
                    tur3 = false;
                    turn3 = false;
                    turn4 = true;
                    player_3_info_balance = num_to_texture(font_dited, rend, three.money, &black);
                }
                else if (three.pos == 9 && turn3 && tur3)
                {
                    three.pos = 27;
                    three.skip = 4;
                    change_rect(&pl3, map[three.pos].x, map[three.pos].y, 20, 20);
                    tur3 = false;
                    turn3 = false;
                    turn4 = true;
                }
                else if (three.pos == 27 && turn3 && tur3)
                {
                    three.skip = 4;
                    tur3 = false;
                    turn3 = false;
                    turn4 = true;
                }
                else if (three.pos == 18 && turn3 && tur3)
                {
                    three.pos += 8;
                    three.money += 100;
                    tur3 = false;
                    turn3 = false;
                    turn4 = true;
                    player_3_info_balance = num_to_texture(font_dited, rend, three.money, &black);
                    change_rect(&pl3, map[three.pos].x, map[three.pos].y, 20, 20);

                }
                else if ((three.pos == 7 || three.pos == 16 || three.pos == 24) && turn3 && tur3 && e.key.keysym.sym == SDLK_RETURN && SDL_KEYUP == e.type)
                {
                    int cn = dice();
                    if (cn == 1)
                    {
                        three.money += 50;
                        currchan = chances[0];
                    }
                    else if (cn == 2)
                    {
                        three.money += 100;
                        currchan = chances[1];
                    }
                    else if (cn == 3)
                    {
                        three.money += 150;
                        currchan = chances[2];
                    }
                    else if (cn == 4)
                    {
                        three.money -= 50;
                        if (three.money < 0)
                            three.money = 0;
                        currchan = chances[3];
                    }
                    else if (cn == 5)
                    {
                        three.money -= 100;
                        if (three.money < 0)
                            three.money = 0;
                        currchan = chances[4];
                    }
                    else if (cn == 6)
                    {
                        three.money -= 150;
                        if (three.money < 0)
                            three.money = 0;
                        currchan = chances[5];
                    }
                    player_3_info_balance = num_to_texture(font_dited, rend, three.money, &black);
                    tur3 = false;
                    turn3 = false;
                    turn4 = true;
                }
                else if ((three.pos == 14 || three.pos == 22) && tur3 && turn3)
                {
                    if (three.pos == 14)
                    {
                        for (int i = 0; i < 36; i++)
                        {
                            if (map[i].index_p == 3)
                            {
                                if (fifty())
                                {
                                    map[i].index_p = 0;
                                    break;
                                }
                                else
                                    continue;
                            }
                        }
                        
                    }
                    else if (three.pos == 22)
                    {
                        for (int i = 0; i < 36; i++)
                        {
                            if (map[i].index_p == 3)
                                map[i].index_p = 0;
                        }
                    }
                    tur3 = false;
                    turn3 = false;
                    turn4 = true;
                }
                else if (three.pos == 0 && turn3 && tur3)
                {
                    tur3 = false;
                    turn3 = false;
                    turn4 = true;
                }
                else if (map[three.pos].cost != 0 && map[three.pos].index_p == 3 && turn3 && tur3)
                {
                    tur3 = false;
                    turn3 = false;
                    turn4 = true;
                }
                if (e.key.keysym.sym == SDLK_RETURN && SDL_KEYUP == e.type && three.skip != 0 && turn4 && !tur4)
                {
                    massege = NULL;
                    currchan = NULL;
                    three.skip--;
                    turn4 = false;
                    tur4 = false;
                    turn1 = true;
                }
                else if(e.key.keysym.sym == SDLK_RETURN && SDL_KEYUP == e.type && turn4 && !tur4)
                {
                    massege = NULL;
                    currchan = NULL;

                    num = dice();
                    four.pos += num;
                    if (four.pos > 35)
                    {
                        four.pos -= 36;
                        four.money += 200;
                    }
                    four.x = map[four.pos].x;
                    four.y = map[four.pos].y;
                    currdice = dicee[num - 1];
                    change_rect(&pl4, four.x, four.y - SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27, SCREEN_HEIGHT / 27);
                    player_4_info_balance = num_to_texture(font_dited, rend, four.money, &black);
                    tur4 = true;
                }
                else if (map[four.pos].key == 1 && turn4 && tur4)
                {
                    massege = wkey;
                    if (e.key.keysym.sym == SDLK_y && SDL_KEYUP == e.type)
                    {
                        if (1000 > three.money)
                        {
                            massege = dmoney;
                            tur4 = false;
                            turn4 = false;
                            turn1 = true;
                        }
                        else
                        {
                            four.opened_chest++;
                            four.money -= 1000;
                            player_4_info_balance = num_to_texture(font_dited, rend, four.money, &black);
                            massege = NULL;
                            map[key_int].key = false;
                            key_int = keygen();
                            map[key_int].key = true;
                            change_rect(&key_gen, map[key_int].x - SCREEN_HEIGHT / 32, map[key_int].y - SCREEN_HEIGHT / 72, SCREEN_HEIGHT / 16, SCREEN_HEIGHT / 36);
                            player_4_info_chests = chests[four.opened_chest];
                            if (four.opened_chest == 4)
                                winn = true;
                            tur4 = false;
                            turn4 = false;
                            turn1 = true;
                        }
                    }
                    else if (e.key.keysym.sym == SDLK_n && SDL_KEYUP == e.type)
                    {
                        massege = NULL;
                        tur4 = false;
                        turn4 = false;
                        turn1 = true;
                    }
                }
                else if (map[four.pos].cost != 0 && map[four.pos].index_p == 0 && turn4 && tur4)
                {
                    massege = want_you;
                    if (e.key.keysym.sym == SDLK_y && SDL_KEYUP == e.type)
                    {
                        if (map[four.pos].cost > four.money)
                        {
                            massege = dmoney;
                            tur4 = false;
                            turn4 = false;
                            turn1 = true;
                        }
                        else
                        {
                            map[four.pos].index_p = 4;
                            four.money -= map[four.pos].cost;
                            player_4_info_balance = num_to_texture(font_dited, rend, four.money, &black);
                            massege = NULL;
                            tur4 = false;
                            turn4 = false;
                            turn1 = true;
                        }
                    }
                    else if (e.key.keysym.sym == SDLK_n && SDL_KEYUP == e.type)
                    {
                        massege = NULL;
                        tur4 = false;
                        turn4 = false;
                        turn1 = true;
                    }
                }
                else if (map[four.pos].cost != 0 && map[four.pos].index_p == 1 && turn4 && tur4)
                {
                    if (four.money < map[four.pos].cost / 2)
                    {
                        one.money += four.money;
                        four.money = 0;
                        tur4 = false;
                        turn4 = false;
                        turn1 = true;
                        player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                        player_4_info_balance = num_to_texture(font_dited, rend, four.money, &black);
                    }
                    else{
                        one.money += map[four.pos].cost / 2;
                        four.money -= map[four.pos].cost / 2;
                        tur4 = false;
                        turn4 = false;
                        turn1 = true;
                        player_1_info_balance = num_to_texture(font_dited, rend, one.money, &black);
                        player_4_info_balance = num_to_texture(font_dited, rend, four.money, &black);
                    }
                }
                else if (map[four.pos].cost != 0 && map[four.pos].index_p == 2 && turn4 && tur4)
                {
                    if (four.money < map[four.pos].cost / 2)
                    {
                        two.money += four.money;
                        four.money = 0;
                        tur4 = false;
                        turn4 = false;
                        turn1 = true;
                        player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                        player_4_info_balance = num_to_texture(font_dited, rend, four.money, &black);
                    }
                    else{
                        two.money += map[four.pos].cost / 2;
                        four.money -= map[four.pos].cost / 2;
                        tur4 = false;
                        turn4 = false;
                        turn1 = true;
                        player_2_info_balance = num_to_texture(font_dited, rend, two.money, &black);
                        player_4_info_balance = num_to_texture(font_dited, rend, four.money, &black);
                    }
                }
                else if (map[one.pos].cost != 0 && map[one.pos].index_p == 3 && turn4 && tur4)
                {
                    if (four.money < map[four.pos].cost / 2)
                    {
                        three.money += four.money;
                        four.money = 0;
                        tur4 = false;
                        turn4 = false;
                        turn1 = true;
                        player_3_info_balance = num_to_texture(font_dited, rend, three.money, &black);
                        player_4_info_balance = num_to_texture(font_dited, rend, four.money, &black);
                    }
                    else{
                        three.money += map[four.pos].cost / 2;
                        four.money -= map[four.pos].cost / 2;
                        tur4 = false;
                        turn4 = false;
                        turn1 = true;
                        player_3_info_balance = num_to_texture(font_dited, rend, three.money, &black);
                        player_4_info_balance = num_to_texture(font_dited, rend, four.money, &black);
                    }
                }
                else if ((four.pos == 3 || four.pos == 29) && tur4 && turn4)
                {
                    if (four.money < 150)
                    {
                        four.money = 0;
                        tur4 = false;
                        turn4 = false;
                        turn1 = true;
                        player_4_info_balance = num_to_texture(font_dited, rend, four.money, &black);
                    }
                    else{
                        four.money -= 150;
                        tur4 = false;
                        turn4 = false;
                        turn1 = true;
                        player_4_info_balance = num_to_texture(font_dited, rend, four.money, &black);
                    }
                }
                else if ((four.pos == 12 || four.pos == 20 || four.pos == 33) && turn4 && tur4)
                {
                    four.money += rand_num();
                    tur4 = false;
                    turn4 = false;
                    turn1 = true;
                    player_4_info_balance = num_to_texture(font_dited, rend, four.money, &black);
                }
                else if (four.pos == 9 && turn4 && tur4)
                {
                    four.pos = 27;
                    four.skip = 4;
                    change_rect(&pl4, map[four.pos].x, map[four.pos].y, 20, 20);
                    tur4 = false;
                    turn4 = false;
                    turn1 = true;
                }
                else if (four.pos == 27 && turn4 && tur4)
                {
                    four.skip = 4;
                    tur4 = false;
                    turn4 = false;
                    turn1 = true;
                }
                else if (four.pos == 18 && turn4 && tur4)
                {
                    four.pos += 8;
                    four.money += 100;
                    tur4 = false;
                    turn4 = false;
                    turn1 = true;
                    player_4_info_balance = num_to_texture(font_dited, rend, four.money, &black);
                    change_rect(&pl4, map[four.pos].x, map[four.pos].y, 20, 20);

                }
                else if ((four.pos == 7 || four.pos == 16 || four.pos == 24) && turn4 && tur4 && e.key.keysym.sym == SDLK_RETURN && SDL_KEYUP == e.type)
                {
                    int cn = dice();
                    if (cn == 1)
                    {
                        four.money += 50;
                        currchan = chances[0];
                    }
                    else if (cn == 2)
                    {
                        four.money += 100;
                        currchan = chances[1];
                    }
                    else if (cn == 3)
                    {
                        four.money += 150;
                        currchan = chances[2];
                    }
                    else if (cn == 4)
                    {
                        four.money -= 50;
                        if (four.money < 0)
                            four.money = 0;
                        currchan = chances[3];
                    }
                    else if (cn == 5)
                    {
                        four.money -= 100;
                        if (four.money < 0)
                            four.money = 0;
                        currchan = chances[4];
                    }
                    else if (cn == 6)
                    {
                        four.money -= 150;
                        if (four.money < 0)
                            four.money = 0;
                        currchan = chances[5];
                    }
                    player_4_info_balance = num_to_texture(font_dited, rend, four.money, &black);
                    tur4 = false;
                    turn4 = false;
                    turn1 = true;
                }
                else if ((four.pos == 14 || four.pos == 22) && tur4 && turn4)
                {
                    if (four.pos == 14)
                    {
                        for (int i = 0; i < 36; i++)
                        {
                            if (map[i].index_p == 4)
                            {
                                if (fifty())
                                {
                                    map[i].index_p = 0;
                                    break;
                                }
                                else
                                    continue;
                            }
                        }
                        
                    }
                    else if (four.pos == 22)
                    {
                        for (int i = 0; i < 36; i++)
                        {
                            if (map[i].index_p == 4)
                                map[i].index_p = 0;
                        }
                    }
                    tur4 = false;
                    turn4 = false;
                    turn1 = true;
                }
                else if (four.pos == 0 && turn4 && tur4)
                {
                    tur4 = false;
                    turn4 = false;
                    turn1 = true;
                }
                else if (map[four.pos].cost != 0 && map[four.pos].index_p == 4 && turn4 && tur4)
                {
                    tur4 = false;
                    turn4 = false;
                    turn1 = true;
                }
            }
        }
        SDL_RenderClear(rend);
        
        SDL_RenderSetViewport(rend, &screen);
        SDL_RenderCopy(rend, current_img, NULL, NULL);

        
        if (!game_is_started)
        {
            SDL_RenderSetViewport(rend, &button1);
            SDL_RenderCopy(rend, current_buttons[0], NULL, NULL);

            SDL_RenderSetViewport(rend, &button2);
            SDL_RenderCopy(rend, current_buttons[1], NULL, NULL);

            SDL_RenderSetViewport(rend, &button3);
            SDL_RenderCopy(rend, current_buttons[2], NULL, NULL);
        }
        else if (game_is_started && !menu_is_open && players == 4)
        {
            for(int i = 0; i < 36; i++)
            {
                if (map[i].index_p == 1){
                    change_rect(&home, map[i].x - 15, map[i].y - 15, 30, 30);
                    SDL_RenderSetViewport(rend, &home);
                    SDL_RenderCopy(rend, homes[0], NULL, NULL);
                }
                else if (map[i].index_p == 2)
                {
                    change_rect(&home, map[i].x - 15, map[i].y - 15, 30, 30);
                    SDL_RenderSetViewport(rend, &home);
                    SDL_RenderCopy(rend, homes[1], NULL, NULL);
                }
                else if (map[i].index_p == 3)
                {
                    change_rect(&home, map[i].x - 15, map[i].y - 15, 30, 30);
                    SDL_RenderSetViewport(rend, &home);
                    SDL_RenderCopy(rend, homes[2], NULL, NULL);
                }
                else if (map[i].index_p == 4)
                {
                    change_rect(&home, map[i].x - 15, map[i].y - 15, 30, 30);
                    SDL_RenderSetViewport(rend, &home);
                    SDL_RenderCopy(rend, homes[3], NULL, NULL);
                }
            }

            SDL_RenderSetViewport(rend, &ui_main);
            SDL_RenderCopy(rend, ui_4, NULL, NULL);


            SDL_RenderSetViewport(rend, &player_1_balance);
            SDL_RenderCopy(rend, player_1_info_balance, NULL, NULL);

            SDL_RenderSetViewport(rend, &player_1_chests);
            SDL_RenderCopy(rend, player_1_info_chests, NULL, NULL);


            SDL_RenderSetViewport(rend, &player_2_balance);
            SDL_RenderCopy(rend, player_2_info_balance, NULL, NULL);

            SDL_RenderSetViewport(rend, &player_2_chests);
            SDL_RenderCopy(rend, player_2_info_chests, NULL, NULL);


            SDL_RenderSetViewport(rend, &player_3_balance);
            SDL_RenderCopy(rend, player_3_info_balance, NULL, NULL);

            SDL_RenderSetViewport(rend, &player_3_chests);
            SDL_RenderCopy(rend, player_3_info_chests, NULL, NULL);


            SDL_RenderSetViewport(rend, &player_4_balance);
            SDL_RenderCopy(rend, player_4_info_balance, NULL, NULL);

            SDL_RenderSetViewport(rend, &player_4_chests);
            SDL_RenderCopy(rend, player_4_info_chests, NULL, NULL);

            SDL_RenderSetViewport(rend, &diice);
            SDL_RenderCopy(rend, currdice, NULL, NULL);

            SDL_RenderSetViewport(rend, &key_gen);
            SDL_RenderCopy(rend, key, NULL, NULL);

            SDL_RenderSetViewport(rend, &pl1);
            SDL_RenderCopy(rend, point1, NULL, NULL);

            SDL_RenderSetViewport(rend, &pl2);
            SDL_RenderCopy(rend, point2, NULL, NULL);

            SDL_RenderSetViewport(rend, &pl3);
            SDL_RenderCopy(rend, point3, NULL, NULL);

            SDL_RenderSetViewport(rend, &pl4);
            SDL_RenderCopy(rend, point4, NULL, NULL);

            SDL_RenderSetViewport(rend, &tur);
            if (turn1)
                SDL_RenderCopy(rend, turn_1, NULL, NULL);
            else if (turn2)
                SDL_RenderCopy(rend, turn_2, NULL, NULL);
            else if (turn3)
                SDL_RenderCopy(rend, turn_3, NULL, NULL);
            else
                SDL_RenderCopy(rend, turn_4, NULL, NULL);
            
            SDL_RenderSetViewport(rend, &prent);
            SDL_RenderCopy(rend, prentr, NULL, NULL);
            
            SDL_RenderSetViewport(rend, &want_buy);
            SDL_RenderCopy(rend, massege, NULL, NULL);

            SDL_RenderSetViewport(rend, &rect_chance);
            SDL_RenderCopy(rend, currchan, NULL, NULL);
        }
        else if (game_is_started && !menu_is_open && players == 3)
        {
            for(int i = 0; i < 36; i++)
            {
                if (map[i].index_p == 1){
                    change_rect(&home, map[i].x - 15, map[i].y - 15, 30, 30);
                    SDL_RenderSetViewport(rend, &home);
                    SDL_RenderCopy(rend, homes[0], NULL, NULL);
                }
                else if (map[i].index_p == 2)
                {
                    change_rect(&home, map[i].x - 15, map[i].y - 15, 30, 30);
                    SDL_RenderSetViewport(rend, &home);
                    SDL_RenderCopy(rend, homes[1], NULL, NULL);
                }
                else if (map[i].index_p == 3)
                {
                    change_rect(&home, map[i].x - 15, map[i].y - 15, 30, 30);
                    SDL_RenderSetViewport(rend, &home);
                    SDL_RenderCopy(rend, homes[2], NULL, NULL);
                }

            }

            SDL_RenderSetViewport(rend, &diice);
            SDL_RenderCopy(rend, currdice, NULL, NULL); 

            SDL_RenderSetViewport(rend, &key_gen);
            SDL_RenderCopy(rend, key, NULL, NULL);

            SDL_RenderSetViewport(rend, &pl1);
            SDL_RenderCopy(rend, point1, NULL, NULL);

            SDL_RenderSetViewport(rend, &pl2);
            SDL_RenderCopy(rend, point2, NULL, NULL);

            SDL_RenderSetViewport(rend, &pl3);
            SDL_RenderCopy(rend, point3, NULL, NULL);

            SDL_RenderSetViewport(rend, &ui_main);
            SDL_RenderCopy(rend, ui_3, NULL, NULL);

            SDL_RenderSetViewport(rend, &player_1_balance);
            SDL_RenderCopy(rend, player_1_info_balance, NULL, NULL);

            SDL_RenderSetViewport(rend, &player_1_chests);
            SDL_RenderCopy(rend, player_1_info_chests, NULL, NULL);

            SDL_RenderSetViewport(rend, &player_2_balance);
            SDL_RenderCopy(rend, player_2_info_balance, NULL, NULL);

            SDL_RenderSetViewport(rend, &player_2_chests);
            SDL_RenderCopy(rend, player_2_info_chests, NULL, NULL);

            SDL_RenderSetViewport(rend, &player_3_balance);
            SDL_RenderCopy(rend, player_3_info_balance, NULL, NULL);  

            SDL_RenderSetViewport(rend, &player_3_chests);
            SDL_RenderCopy(rend, player_3_info_chests, NULL, NULL);

            SDL_RenderSetViewport(rend, &tur);
            if (turn1)
                SDL_RenderCopy(rend, turn_1, NULL, NULL);
            else if (turn2)
                SDL_RenderCopy(rend, turn_2, NULL, NULL);
            else 
                SDL_RenderCopy(rend, turn_3, NULL, NULL);
            
            SDL_RenderSetViewport(rend, &prent);
            SDL_RenderCopy(rend, prentr, NULL, NULL);
            
            SDL_RenderSetViewport(rend, &want_buy);
            SDL_RenderCopy(rend, massege, NULL, NULL);

            SDL_RenderSetViewport(rend, &rect_chance);
            SDL_RenderCopy(rend, currchan, NULL, NULL);
        }
        else if (game_is_started && !menu_is_open && players == 2)
        {
            for(int i = 0; i < 36; i++)
            {
                if (map[i].index_p == 1){
                    change_rect(&home, map[i].x - 15, map[i].y - 15, 30, 30);
                    SDL_RenderSetViewport(rend, &home);
                    SDL_RenderCopy(rend, homes[0], NULL, NULL);
                }
                else if (map[i].index_p == 2)
                {
                    change_rect(&home, map[i].x - 15, map[i].y - 15, 30, 30);
                    SDL_RenderSetViewport(rend, &home);
                    SDL_RenderCopy(rend, homes[1], NULL, NULL);
                }

            }

            SDL_RenderSetViewport(rend, &diice);
            SDL_RenderCopy(rend, currdice, NULL, NULL); 

            SDL_RenderSetViewport(rend, &key_gen);
            SDL_RenderCopy(rend, key, NULL, NULL);

            SDL_RenderSetViewport(rend, &pl1);
            SDL_RenderCopy(rend, point1, NULL, NULL);

            SDL_RenderSetViewport(rend, &pl2);
            SDL_RenderCopy(rend, point2, NULL, NULL);

            SDL_RenderSetViewport(rend, &ui_main);
            SDL_RenderCopy(rend, ui_2, NULL, NULL);

            SDL_RenderSetViewport(rend, &player_1_balance);
            SDL_RenderCopy(rend, player_1_info_balance, NULL, NULL);

            SDL_RenderSetViewport(rend, &player_1_chests);
            SDL_RenderCopy(rend, player_1_info_chests, NULL, NULL);


            SDL_RenderSetViewport(rend, &player_2_balance);
            SDL_RenderCopy(rend, player_2_info_balance, NULL, NULL);

            SDL_RenderSetViewport(rend, &player_2_chests);
            SDL_RenderCopy(rend, player_2_info_chests, NULL, NULL);

            SDL_RenderSetViewport(rend, &tur);
            if (turn1)
                SDL_RenderCopy(rend, turn_1, NULL, NULL);
            else   
                SDL_RenderCopy(rend, turn_2, NULL, NULL);

            SDL_RenderSetViewport(rend, &prent);
            SDL_RenderCopy(rend, prentr, NULL, NULL);
            
            SDL_RenderSetViewport(rend, &want_buy);
            SDL_RenderCopy(rend, massege, NULL, NULL);

            SDL_RenderSetViewport(rend, &rect_chance);
            SDL_RenderCopy(rend, currchan, NULL, NULL);
        }
        else if (menu_is_open && !settings && !quest)
        {
            SDL_RenderSetViewport(rend, &button1);
            SDL_RenderCopy(rend, current_buttons[0], NULL, NULL);

            SDL_RenderSetViewport(rend, &button2);
            SDL_RenderCopy(rend, current_buttons[1], NULL, NULL);
        }
        else if (menu_is_open && !settings && quest)
        {
            SDL_RenderSetViewport(rend ,&aus);
            SDL_RenderCopy(rend, leave, NULL, NULL);        
        }
        else if (menu_is_open && settings && !quest)
        {
            SDL_RenderSetViewport(rend, &button1);
            SDL_RenderCopy(rend, current_buttons[0], NULL, NULL);

            SDL_RenderSetViewport(rend, &button2);
            SDL_RenderCopy(rend, current_buttons[1], NULL, NULL);

            SDL_RenderSetViewport(rend, &button3);
            SDL_RenderCopy(rend, current_buttons[2], NULL, NULL);           
        }
        if(winn && !menu_is_open)
        {
            if (one.opened_chest == 4)
                winner = winners[0];
            else if (two.opened_chest == 4)
                winner = winners[1];
            else if (three.opened_chest == 4)
                winner = winners[2];
            else if (four.opened_chest == 4)
                winner = winners[3];
            SDL_RenderSetViewport(rend, &want_buy);
            SDL_RenderCopy(rend, winner, NULL, NULL);
        }

        SDL_RenderPresent(rend);
        if (game_is_started)
        {
            if (players == 3)
            {
                player one;
                one.pos = 0;
                one.money = 700;
                player two;
                two.pos = 0;
                two.money = 700;
                player three;
                three.pos = 0;
                three.money = 700;
            }
            else if (players == 4)
            {
                player one;
                one.pos = 0;
                one.money = 700;
                player two;
                two.pos = 0;
                two.money = 700;
                player three;
                three.pos = 0;
                three.money = 700;
                player four;
                four.pos = 0;
                four.money = 700;
            }
        }
    }
    
    destroyTexture(leave);
    destroyTexture(agry);
    destroyTexture(disagry);
    destroyTexture(map_img);
    destroyTexture(point1);
    destroyTexture(point2);
    destroyTexture(point3);
    destroyTexture(point4);
    destroyTexture(start_array);
    destroyTexture(menu_array);
    destroyTexture(settings_background);
    destroyTexture(currdice);
    for (int i = 0; i < 6; i++)
    {
        destroyTexture(dicee[i]);
    }
    
    for (int i = 0; i < 9; i++)
    {
        destroyTexture(img_array[i]);
    }
    for (int i = 0; i < 3; i++)
    {
        destroyTexture(current_buttons[i]);
    }
    

    quit();
}
