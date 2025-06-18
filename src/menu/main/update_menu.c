/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** update_menu.c
*/

#include "wolf3d.h"

void main_render(sfml_t *sfml)
{
    sfRenderWindow_setView(sfml->window, sfml->game->cameras->camMenu);
    render_color(sfml);
    sfRenderWindow_drawSprite(sfml->window, sfml->menu->start_b->sprite, NULL);
    sfRenderWindow_drawSprite(sfml->window, sfml->menu->options_b->sprite,
        NULL);
    sfRenderWindow_drawSprite(sfml->window, sfml->menu->exit_b->sprite,
        NULL);
    sfRenderWindow_drawSprite(sfml->window, sfml->menu->back_b->sprite,
        NULL);
    sfRenderWindow_drawSprite(sfml->window, sfml->menu->doom_sprite, NULL);
    update_skull(sfml, sfml->menu->skull_sheet);
    sfRenderWindow_drawSprite(sfml->window, sfml->menu->skull_sheet->sprite,
        NULL);
}

void update_menu(sfml_t *sfml)
{
    sfRenderWindow_drawSprite(sfml->window, sfml->menu->bg_sprite, NULL);
    if (!sfml->menu->intro)
        main_render(sfml);
}
