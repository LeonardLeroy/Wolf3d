/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** is_wall.c
*/

#include "wolf3d.h"

int is_wall(sfml_t *sfml, float x, float y)
{
    int map_x = floor(x / TILE_SIZE);
    int map_y = floor(y / TILE_SIZE);

    if (map_x < 0 || map_x >= MAP_WIDTH || map_y < 0 || map_y >= MAP_HEIGHT)
        return 1;
    return sfml->game->map[map_y][map_x];
}
