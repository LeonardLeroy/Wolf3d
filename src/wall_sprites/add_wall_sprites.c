/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** add_wall_sprites.c
*/

#include "wolf3d.h"

static void resize_sprites_manager(wall_sprites_manager_t *manager)
{
    wall_sprite_t *new_sprites;

    manager->capacity *= 2;
    new_sprites = salloc(sizeof(wall_sprite_t) * manager->capacity);
    memcpy(new_sprites, manager->sprites, sizeof(wall_sprite_t) *
        manager->count);
    free(manager->sprites);
    manager->sprites = new_sprites;
}

static void init_sprite(wall_sprite_t *sprite, sprite_params_t params)
{
    sprite->x = params.x;
    sprite->y = params.y;
    sprite->texture_id = params.texture_id;
    sprite->size = params.size;
    sprite->is_visible = 0;
    sprite->distance = 0.0f;
    sprite->angle = 0.0f;
}

void add_sprite(sfml_t *sfml, sprite_params_t params)
{
    wall_sprites_manager_t *manager = sfml->game->sprites;

    if (manager->count >= manager->capacity)
        resize_sprites_manager(manager);
    init_sprite(&manager->sprites[manager->count], params);
    manager->count++;
}
