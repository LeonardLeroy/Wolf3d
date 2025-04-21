/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** init_player.c
*/

#include "wolf3d.h"

void init_player(sfml_t *sfml)
{
    sfml->game->player = salloc(sizeof(player_t));
    sfml->game->player->x = TILE_SIZE + TILE_SIZE / 2;
    sfml->game->player->y = TILE_SIZE + TILE_SIZE / 2;
    sfml->game->player->angle = PI / 2;
}
