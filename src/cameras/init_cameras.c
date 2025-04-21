/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** init_cameras.c
*/

#include "wolf3d.h"

void init_cameras(sfml_t *sfml)
{
    sfVector2u window_size = sfRenderWindow_getSize(sfml->window);

    sfml->game->cameras = salloc(sizeof(cameras_t));
    sfml->game->cameras->camGame = sfView_create();
    sfView_setSize(sfml->game->cameras->camGame,
        (sfVector2f){window_size.x, window_size.y});
    sfView_setCenter(sfml->game->cameras->camGame,
        (sfVector2f){window_size.x / 2,
            (window_size.y / 2) +
            sfSprite_getScale(sfml->game->hud->stbar).y + PLAYER_HEIGHT});
    sfml->game->cameras->camHUD = sfView_create();
    sfView_setSize(sfml->game->cameras->camHUD,
        (sfVector2f){window_size.x, window_size.y});
    sfView_setCenter(sfml->game->cameras->camHUD,
        (sfVector2f){window_size.x / 2, window_size.y / 2});
}
