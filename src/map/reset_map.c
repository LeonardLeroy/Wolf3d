/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** reset_map.c
*/

#include "wolf3d.h"

void reset_map(sfml_t *sfml)
{
    sfml->game->player->x = TILE_SIZE + TILE_SIZE / 2;
    sfml->game->player->y = TILE_SIZE + TILE_SIZE / 2;
    sfml->game->player->angle = PI / 2;
    for (int i = 2; i < MAP_HEIGHT - 2; i++) {
        for (int j = 2; j < MAP_WIDTH - 2; j++)
            determine_map_content(sfml, i, j);
    }
    sfml->game->map[1][1] = 0;
}
