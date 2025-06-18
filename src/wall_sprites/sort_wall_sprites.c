/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** sort_wall_sprites.c
*/

#include "wolf3d.h"

static int compare_sprites(const void *a, const void *b)
{
    wall_sprite_t *sprite_a = (wall_sprite_t *)a;
    wall_sprite_t *sprite_b = (wall_sprite_t *)b;

    if (sprite_a->distance > sprite_b->distance)
        return -1;
    if (sprite_a->distance < sprite_b->distance)
        return 1;
    return 0;
}

void sort_sprites_by_distance(sfml_t *sfml)
{
    wall_sprites_manager_t *manager = sfml->game->sprites;

    qsort(manager->sprites, manager->count,
        sizeof(wall_sprite_t), compare_sprites);
}
