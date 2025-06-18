/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** update.c
*/

#include "wolf3d.h"

void update_game(sfml_t *sfml)
{
    draw(sfml);
    update_hud(sfml);
    update_player(sfml);
    update_enemies(sfml, sfml->game->ai_manager);
    update_particles(sfml);
}

void update(sfml_t *sfml)
{
    update_clock(sfml);
    sfml->update_f(sfml);
    if (sfml->state == MENU || sfml->state == WIN_LOSE)
        update_mouse(sfml);
}
