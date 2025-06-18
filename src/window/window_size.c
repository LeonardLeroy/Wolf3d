/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** window_size.c
*/

#include "wolf3d.h"

void update_window_size(sfml_t *sfml, unsigned int new_width,
    unsigned int new_height)
{
    if (!sfml->window_size)
        return;
    if (new_width < 800)
        new_width = 800;
    if (new_height < 600)
        new_height = 600;
    sfml->window_size->width = new_width;
    sfml->window_size->height = new_height;
    sfml->window_size->scale_factor_x = (float)new_width / WINDOW_WIDTH;
    sfml->window_size->scale_factor_y = (float)new_height / WINDOW_HEIGHT;
}

void update_menu_background(sfml_t *sfml)
{
    sfVector2u window_size;
    sfVector2u texture_size;
    float scale_x;
    float scale_y;
    float scale;

    if (!sfml->menu || !sfml->menu->bg_sprite)
        return;
    window_size = sfRenderWindow_getSize(sfml->window);
    texture_size = sfTexture_getSize(sfml->menu->bg_texture);
    scale_x = (float)window_size.x / texture_size.x;
    scale_y = (float)window_size.y / texture_size.y;
    scale = (scale_x < scale_y) ? scale_x : scale_y;
    sfSprite_setScale(sfml->menu->bg_sprite, (sfVector2f){scale, scale});
    sfSprite_setPosition(sfml->menu->bg_sprite, (sfVector2f){
        (window_size.x - (texture_size.x * scale)) / 2,
        (window_size.y - (texture_size.y * scale)) / 2
    });
}

float get_scale_factor(sfml_t *sfml)
{
    if (!sfml->window_size)
        return 1.0f;
    return fminf(sfml->window_size->scale_factor_x,
        sfml->window_size->scale_factor_y);
}
