/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** init_window.c
*/

#include "wolf3d.h"

void init_window(sfml_t *sfml)
{
    sfml->window = sfRenderWindow_create(
        (sfVideoMode){WINDOW_WIDTH, WINDOW_HEIGHT, 32},
        "Wolf3d", sfClose, NULL
    );
    sfRenderWindow_setVerticalSyncEnabled(sfml->window, 1);
    sfRenderWindow_setMouseCursorVisible(sfml->window, sfFalse);
}
