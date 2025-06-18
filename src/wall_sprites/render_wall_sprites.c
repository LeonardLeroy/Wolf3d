/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** render_wall_sprites.c
*/

#include "wolf3d.h"

static void render_sprite(sfml_t *sfml, wall_sprite_t *sprite)
{
    sfVector2u window_size = sfRenderWindow_getSize(sfml->window);
    float distance_proj_plane = (window_size.y / 2) / tanf(FOV / 2);
    float spr_height = (TILE_SIZE * sprite->size / sprite->distance) *
        distance_proj_plane;
    float spr_width = spr_height;
    float spr_screen_x = window_size.x / 2 + tanf(sprite->angle) *
        distance_proj_plane;
    float spr_left = spr_screen_x - spr_width / 2;
    float spr_top = window_size.y / 2 - spr_height / 2;
    sfRectangleShape *spr_shape = sfRectangleShape_create();
    float brightness = 1.0f / (1.0f + sprite->distance * 0.008f);

    sfRectangleShape_setSize(spr_shape, (sfVector2f){spr_width, spr_height});
    sfRectangleShape_setPosition(spr_shape, (sfVector2f){spr_left, spr_top});
    sfRectangleShape_setFillColor(spr_shape, sfColor_fromRGB(255 *
        brightness, 255 * brightness, 255 * brightness));
    sfRenderWindow_drawRectangleShape(sfml->window, spr_shape, NULL);
    sfRectangleShape_destroy(spr_shape);
}

void render_sprites(sfml_t *sfml)
{
    wall_sprites_manager_t *manager = sfml->game->sprites;
    wall_sprite_t *sprite;

    find_visible_sprites(sfml);
    for (int i = 0; i < manager->count; i++) {
        sprite = &manager->sprites[i];
        if (sprite->is_visible)
            render_sprite(sfml, sprite);
    }
}
