/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-evan.lafolie
** File description:
** bss.c
*/

#include "wolf3d.h"

static int is_sprite_visible(sfml_t *sfml, wall_sprite_t *sprite)
{
    float angle_to_center;
    int ray_index;

    if (!sprite->is_visible)
        return 0;
    angle_to_center = normalize_angle(sprite->angle);
    if (angle_to_center > PI)
        angle_to_center -= 2 * PI;
    ray_index = (int)((angle_to_center + FOV / 2) * NUM_RAYS / FOV);
    if (ray_index < 0 || ray_index >= NUM_RAYS)
        return 0;
    return sprite->distance < sfml->game->rays[ray_index].distance;
}

static void binary_search_visible_sprites(sfml_t *sfml, int start, int end)
{
    int mid = start + (end - start) / 2;
    wall_sprite_t *sprite = &sfml->game->sprites->sprites[mid];

    if (start > end)
        return;
    sprite->is_visible = is_sprite_visible(sfml, sprite);
    if (sprite->is_visible) {
        binary_search_visible_sprites(sfml, start, mid - 1);
        binary_search_visible_sprites(sfml, mid + 1, end);
        return;
    }
    if (sprite->angle < - FOV / 2) {
        binary_search_visible_sprites(sfml, mid + 1, end);
    } else if (sprite->angle > FOV / 2) {
        binary_search_visible_sprites(sfml, start, mid - 1);
    } else {
        binary_search_visible_sprites(sfml, start, mid - 1);
        binary_search_visible_sprites(sfml, mid + 1, end);
    }
}

void find_visible_sprites(sfml_t *sfml)
{
    wall_sprites_manager_t *manager = sfml->game->sprites;

    if (manager->count == 0)
        return;
    update_sprites(sfml);
    sort_sprites_by_distance(sfml);
    binary_search_visible_sprites(sfml, 0, manager->count - 1);
}
