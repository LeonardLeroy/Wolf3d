/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** draw.c
*/

#include "wolf3d.h"

void draw_hud(sfml_t *sfml)
{
    sfRenderWindow_drawSprite(sfml->window, sfml->game->hud->stbar, NULL);
    sfRenderWindow_drawSprite(sfml->window, sfml->game->hud->doom_guy, NULL);
}

void draw(sfml_t *sfml)
{
    sfRenderWindow_setView(sfml->window, sfml->game->cameras->camGame);
    cast_all_rays(sfml);
    render_walls(sfml);
    sfRenderWindow_setView(sfml->window, sfml->game->cameras->camHUD);
    draw_hud(sfml);
}
