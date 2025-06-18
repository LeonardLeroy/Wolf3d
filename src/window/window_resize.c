/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-evan.lafolie
** File description:
** window_resize.c
*/

#include "wolf3d.h"

static void handle_cam_menu(game_t *game, sfVector2u new_size)
{
    if (game->cameras->camMenu) {
        sfView_setSize(game->cameras->camMenu, (sfVector2f){new_size.x,
            new_size.y});
        sfView_setCenter(game->cameras->camMenu, (sfVector2f){new_size.x / 2,
            new_size.y / 2});
    }
}

static void update_game_cameras(game_t *game, sfVector2u new_size)
{
    if (!game || !game->cameras)
        return;
    if (game->cameras->camGame && game->game_substate == NORMAL) {
        sfView_setSize(game->cameras->camGame, (sfVector2f){new_size.x,
            new_size.y});
        sfView_setCenter(game->cameras->camGame, (sfVector2f){new_size.x / 2,
            (new_size.y / 2) + PLAYER_HEIGHT});
    }
    if (game->cameras->camHUD) {
        sfView_setSize(game->cameras->camHUD, (sfVector2f){new_size.x,
            new_size.y});
        sfView_setCenter(game->cameras->camHUD, (sfVector2f){new_size.x / 2,
            new_size.y / 2});
        if (game->hud && game->hud->stbar)
            sfSprite_getGlobalBounds(game->hud->stbar);
        sfView_setViewport(game->cameras->camHUD, (sfFloatRect){0, 0, 1, 1});
    }
    handle_cam_menu(game, new_size);
}

static void update_weapons_on_resize(sfml_t *sfml)
{
    sfVector2f new_pos;
    float new_scale;
    weapon_t *weapon;

    if (!sfml->game || !sfml->game->weapons)
        return;
    new_scale = get_scale_factor(sfml);
    for (int i = 0; i < WEAPONS_AMOUNT; i++) {
        if (sfml->game->weapons[i] && sfml->game->weapons[i]->sheet) {
            weapon = sfml->game->weapons[i];
            sfSprite_setScale(weapon->sheet->sprite,
                (sfVector2f){4.0f * new_scale, 4.0f * new_scale});
            new_pos = calculate_weapon_position(sfml, weapon);
            sfSprite_setPosition(weapon->sheet->sprite, new_pos);
            weapon->base_x = new_pos.x;
            weapon->base_y = new_pos.y;
        }
    }
}

static void update_menu_on_resize(sfml_t *sfml)
{
    if (!sfml->menu)
        return;
    update_menu_background(sfml);
    update_main_menu_positions(sfml);
    if (sfml->menu->options)
        update_options_menu_positions(sfml);
    if (sfml->menu->saves)
        update_saves_menu_positions(sfml);
}

void handle_window_resize(sfml_t *sfml)
{
    sfVector2u new_size = sfRenderWindow_getSize(sfml->window);

    update_window_size(sfml, new_size.x, new_size.y);
    update_game_cameras(sfml->game, new_size);
    if (sfml->game && sfml->game->hud) {
        free_hud(sfml);
        init_hud(sfml);
    }
    update_weapons_on_resize(sfml);
    update_menu_on_resize(sfml);
    update_win_lose_positions(sfml);
}
