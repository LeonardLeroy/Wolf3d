/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** init_cameras.c
*/

#include "wolf3d.h"

static void init_cam_game(sfml_t *sfml, sfVector2u window_size)
{
    sfml->game->cameras->camGame = sfView_create();
    sfView_setSize(sfml->game->cameras->camGame,
        (sfVector2f){window_size.x, window_size.y});
    sfView_setCenter(sfml->game->cameras->camGame,
        (sfVector2f){window_size.x / 2,
            (window_size.y / 2) +
            sfSprite_getScale(sfml->game->hud->stbar).y + PLAYER_HEIGHT});
}

static void init_cam_hud(sfml_t *sfml, sfVector2u window_size)
{
    sfml->game->cameras->camHUD = sfView_create();
    sfView_setSize(sfml->game->cameras->camHUD,
        (sfVector2f){window_size.x, window_size.y});
    sfView_setCenter(sfml->game->cameras->camHUD,
        (sfVector2f){window_size.x / 2, window_size.y / 2});
}

static void init_cam_menu(sfml_t *sfml, sfVector2u window_size)
{
    sfml->game->cameras->camMenu = sfView_create();
    sfView_setSize(sfml->game->cameras->camMenu,
        (sfVector2f){window_size.x, window_size.y});
    sfView_setCenter(sfml->game->cameras->camMenu,
        (sfVector2f){window_size.x / 2, window_size.y / 2});
}

void init_cameras(sfml_t *sfml)
{
    sfVector2u window_size = sfRenderWindow_getSize(sfml->window);

    sfml->game->cameras = salloc(sizeof(cameras_t));
    init_cam_game(sfml, window_size);
    init_cam_hud(sfml, window_size);
    init_cam_menu(sfml, window_size);
}
