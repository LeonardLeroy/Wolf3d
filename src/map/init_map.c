/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** init_map.c
*/

#include "wolf3d.h"

static void determine_map_borders(sfml_t *sfml, int i, int j)
{
    if (i == 0 || j == 0 || i == MAP_HEIGHT - 1 || j == MAP_WIDTH - 1)
        sfml->game->map[i][j] = 1;
    else
        sfml->game->map[i][j] = 0;
}

static void determine_map_content(sfml_t *sfml, int i, int j)
{
    if (rand() % 5 == 0)
        sfml->game->map[i][j] = 1;
}

void init_map(sfml_t *sfml)
{
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++)
            determine_map_borders(sfml, i, j);
    }
    for (int i = 2; i < MAP_HEIGHT - 2; i++) {
        for (int j = 2; j < MAP_WIDTH - 2; j++)
            determine_map_content(sfml, i, j);
    }
    sfml->game->map[1][1] = 0;
}
