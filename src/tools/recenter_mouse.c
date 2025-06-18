/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** recenter_mouse.c
*/

#include "wolf3d.h"

void recenter_mouse(sfml_t *sfml)
{
    sfVector2u window_size = sfRenderWindow_getSize(sfml->window);

    sfMouse_setPositionRenderWindow((sfVector2i){window_size.x / 2,
        window_size.y / 2}, sfml->window);
}
