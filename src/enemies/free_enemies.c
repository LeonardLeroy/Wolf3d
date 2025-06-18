/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** free_enemies.c
*/

#include "wolf3d.h"

void free_enemy(enemy_t *enemy)
{
    if (!enemy)
        return;
    enemy->current = NULL;
    free_sprite_sheet(enemy->walk);
    free_sprite_sheet(enemy->shoot);
    free_sprite_sheet(enemy->death);
    free_sprite_sheet(enemy->hurt);
    free(enemy);
}

void free_enemies(sfml_t *sfml)
{
    if (!sfml->game->enemies)
        return;
    for (int i = 0; i < NUM_ENEMIES; i++)
        free_enemy(sfml->game->enemies[i]);
    free(sfml->game->enemies);
    sfml->game->enemies = NULL;
}
