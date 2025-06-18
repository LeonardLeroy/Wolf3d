/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** init_window.c
*/

#include "wolf3d.h"

void init_window_size(sfml_t *sfml)
{
    sfml->window_size = salloc(sizeof(window_size_t));
    sfml->window_size->width = WINDOW_WIDTH;
    sfml->window_size->height = WINDOW_HEIGHT;
    sfml->window_size->scale_factor_x = 1.0f;
    sfml->window_size->scale_factor_y = 1.0f;
}

void init_window(sfml_t *sfml)
{
    if (sfml->window)
        return;
    sfml->window = sfRenderWindow_create(
        (sfVideoMode){sfml->window_size->width, sfml->window_size->height, 32},
        "Wolf3d", sfResize | sfClose, NULL
    );
    sfRenderWindow_setVerticalSyncEnabled(sfml->window, 1);
    sfRenderWindow_setMouseCursorVisible(sfml->window, 0);
}
