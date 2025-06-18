/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** update_wall_sprites.c
*/

#include "wolf3d.h"

static void calculate_sprite_attributes(wall_sprite_t *sprite,
    player_t *player)
{
    float dx = sprite->x - player->x;
    float dy = sprite->y - player->y;
    float half_fov = FOV / 2;

    sprite->distance = sqrtf(dx * dx + dy * dy);
    sprite->angle = atan2f(dy, dx) - player->angle;
    sprite->angle = normalize_angle(sprite->angle);
    sprite->is_visible = (sprite->angle > - half_fov && sprite->angle <
        half_fov);
}

void update_sprites(sfml_t *sfml)
{
    wall_sprites_manager_t *manager = sfml->game->sprites;
    player_t *player = sfml->game->player;

    for (int i = 0; i < manager->count; i++)
        calculate_sprite_attributes(&manager->sprites[i], player);
}
