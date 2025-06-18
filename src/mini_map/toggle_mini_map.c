/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** toggle_mini_map.c
*/

#include "wolf3d.h"

void toggle_mini_map(sfml_t *sfml)
{
    sfVector2u window = sfRenderWindow_getSize(sfml->window);

    if (sfml->game->game_substate == NORMAL) {
        sfml->game->game_substate = MINI_MAP;
        sfView_setSize(sfml->game->cameras->camGame,
            (sfVector2f){MINI_MAP_MIN_ZOOM_X * 1.75,
                MINI_MAP_MIN_ZOOM_Y * 1.75});
    } else {
        sfml->game->game_substate = NORMAL;
        sfView_setSize(sfml->game->cameras->camGame,
            (sfVector2f){window.x, window.y});
        sfView_setCenter(sfml->game->cameras->camGame,
            (sfVector2f){window.x / 2,
                (window.y / 2) +
                sfSprite_getScale(sfml->game->hud->stbar).y + PLAYER_HEIGHT});
    }
}
