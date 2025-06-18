/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** init_wall_sprites.c
*/

#include "wolf3d.h"

void init_sprites(sfml_t *sfml)
{
    sfml->game->sprites = salloc(sizeof(wall_sprites_manager_t));
    sfml->game->sprites->capacity = 32;
    sfml->game->sprites->count = 0;
    sfml->game->sprites->sprites = salloc(sizeof(wall_sprite_t) *
        sfml->game->sprites->capacity);
}

void free_sprites(sfml_t *sfml)
{
    if (!sfml->game->sprites)
        return;
    if (sfml->game->sprites->sprites) {
        free(sfml->game->sprites->sprites);
        sfml->game->sprites->sprites = NULL;
    }
    free(sfml->game->sprites);
    sfml->game->sprites = NULL;
}
