/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** init_game.c
*/

#include "wolf3d.h"

void init_game(sfml_t *sfml)
{
    sfml->game = salloc(sizeof(game_t));
    sfml->game->rays = salloc(sizeof(ray_t) * NUM_RAYS);
    for (int i = 0; i < NUM_RAYS; i++)
        init_rays(&sfml->game->rays[i]);
    init_player(sfml);
    init_hud(sfml);
    init_cameras(sfml);
}
