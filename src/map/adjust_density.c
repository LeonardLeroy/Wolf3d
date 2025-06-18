/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-evan.lafolie
** File description:
** adjust_density.c
*/

#include "wolf3d.h"

static int count_walls(sfml_t *sfml)
{
    int wall_count = 0;

    for (int y = 1; y < MAP_HEIGHT - 1; y++) {
        for (int x = 1; x < MAP_WIDTH - 1; x++)
            wall_count += (sfml->game->map[y][x] == 1);
    }
    return wall_count;
}

static void reduce_wall_density(sfml_t *sfml, float current_ratio,
    int total_cells)
{
    int walls_to_remove = (current_ratio - TARGET_RATIO) * total_cells * 0.5f;
    int x;
    int y;

    for (int i = 0; i < walls_to_remove; i++) {
        x = 1 + rand() % (MAP_WIDTH - 2);
        y = 1 + rand() % (MAP_HEIGHT - 2);
        if (sfml->game->map[y][x] == 1)
            sfml->game->map[y][x] = 0;
    }
}

static void increase_wall_density(sfml_t *sfml, float current_ratio,
    int total_cells)
{
    int walls_to_add = (TARGET_RATIO - current_ratio) * total_cells * 0.3f;
    int x;
    int y;

    for (int i = 0; i < walls_to_add; i++) {
        x = 1 + rand() % (MAP_WIDTH - 2);
        y = 1 + rand() % (MAP_HEIGHT - 2);
        if (sfml->game->map[y][x] == 0 &&
            count_wall_neighbors(sfml, x, y, 1) < 4)
            sfml->game->map[y][x] = 1;
    }
}

void adjust_density(sfml_t *sfml)
{
    int wall_count = count_walls(sfml);
    int total_cells = (MAP_WIDTH - 2) * (MAP_HEIGHT - 2);
    float current_ratio = (float)wall_count / total_cells;
    const float tolerance = 0.05f;

    if (current_ratio > TARGET_RATIO + tolerance)
        reduce_wall_density(sfml, current_ratio, total_cells);
    else if (current_ratio < TARGET_RATIO - tolerance)
        increase_wall_density(sfml, current_ratio, total_cells);
}
