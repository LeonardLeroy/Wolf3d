/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** get_center.c
*/

#include "wolf3d.h"

float get_centered_y(sfml_t *sfml, sfSprite *sprite)
{
    float window_height = (float)sfRenderWindow_getSize(sfml->window).y;
    sfFloatRect sprite_bounds = sfSprite_getGlobalBounds(sprite);
    float sprite_height = sprite_bounds.height;
    float centered_y = (window_height / 2) - (sprite_height / 2);

    return centered_y;
}

float get_centered_x(sfml_t *sfml, sfSprite *sprite)
{
    float window_width = (float)sfRenderWindow_getSize(sfml->window).x;
    sfFloatRect sprite_bounds = sfSprite_getGlobalBounds(sprite);
    float sprite_width = sprite_bounds.width;
    float centered_x = (window_width / 2) - (sprite_width / 2);

    return centered_x;
}
