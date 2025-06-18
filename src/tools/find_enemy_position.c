/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** find_enemy_position.c
*/

#include "wolf3d.h"

static void is_max_attempts(enemy_t *enemy, int attempts, int max_attempts)
{
    if (attempts >= max_attempts) {
        enemy->x = 1;
        enemy->y = 1;
        enemy->world_x = TILE_SIZE + TILE_SIZE / 2;
        enemy->world_y = TILE_SIZE + TILE_SIZE / 2;
    }
}

int is_wall_at_grid(sfml_t *sfml, int x, int y)
{
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
        return 1;
    return sfml->game->map[y][x];
}

void find_enemy_position(sfml_t *sfml, enemy_t *enemy)
{
    int attempts = 0;
    int max_attempts = 100;
    int x;
    int y;

    while (attempts < max_attempts) {
        x = rand() % (MAP_WIDTH + 2) - 1;
        y = rand() % (MAP_HEIGHT + 2) - 1;
        if (is_wall_at_grid(sfml, x, y) == 0) {
            enemy->x = x;
            enemy->y = y;
            enemy->world_x = x * TILE_SIZE + TILE_SIZE / 2;
            enemy->world_y = y * TILE_SIZE + TILE_SIZE / 2;
            return;
        }
        attempts++;
    }
    is_max_attempts(enemy, attempts, max_attempts);
}
