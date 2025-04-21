/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** ray_utils.c
*/

#include "wolf3d.h"

float calculate_actual_distance(float x1, float y1, float x2, float y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

int is_within_bounds(float x, float y)
{
    return (x >= 0 && x < MAP_WIDTH * TILE_SIZE &&
        y >= 0 && y < MAP_HEIGHT * TILE_SIZE);
}

void init_next_coordinates(float xintercept, float yintercept,
    float *next_x, float *next_y)
{
    *next_x = xintercept;
    *next_y = yintercept;
}

void adjust_for_ray_direction(float ray_angle, float next_coord,
    float *check_coord, int is_x_axis)
{
    if ((is_x_axis && is_ray_facing_left(ray_angle)) ||
        (!is_x_axis && is_ray_facing_up(ray_angle))) {
        *check_coord = next_coord - 1;
    } else {
        *check_coord = next_coord;
    }
}

int check_wall_hit(sfml_t *sfml, collision_check_t check, int ray_id)
{
    int map_x = floor(check.check_x / TILE_SIZE);
    int map_y = floor(check.check_y / TILE_SIZE);

    if (is_wall(sfml, check.check_x, check.check_y)) {
        sfml->game->rays[ray_id].wall_hit_x = check.next_x;
        sfml->game->rays[ray_id].wall_hit_y = check.next_y;
        if (map_x >= 0 && map_x < MAP_WIDTH &&
            map_y >= 0 && map_y < MAP_HEIGHT)
            sfml->game->rays[ray_id].wall_hit_content =
                sfml->game->map[map_y][map_x];
        sfml->game->rays[ray_id].was_hit_vertical = 0;
        return 1;
    }
    return 0;
}
