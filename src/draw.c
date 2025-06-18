/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** draw.c
*/

#include "wolf3d.h"

void draw_game(sfml_t *sfml)
{
    sfRenderWindow_setView(sfml->window, sfml->game->cameras->camGame);
    cast_all_rays(sfml);
    render_surfaces(sfml);
    render_sprites(sfml);
    draw_enemies(sfml);
    draw_particles(sfml);
    sfRenderWindow_setView(sfml->window, sfml->game->cameras->camHUD);
    draw_weapon(sfml);
    draw_hud(sfml);
}

void draw(sfml_t *sfml)
{
    switch (sfml->game->game_substate) {
        case NORMAL:
            draw_game(sfml);
            break;
        case MINI_MAP:
            sfRenderWindow_setView(sfml->window, sfml->game->cameras->camGame);
            render_mini_map(sfml);
            break;
        default:
            break;
    }
    update_weapon(sfml, sfml->game->player->weapon);
}
