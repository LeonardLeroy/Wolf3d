/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** raycasting.c
*/

#include "wolf3d.h"

static float get_min_distance(float dist1, float dist2)
{
    return (dist1 < dist2) ? dist1 : dist2;
}

static void set_ray_data(sfml_t *sfml, int ray_id, float distance, float angle)
{
    sfml->game->rays[ray_id].distance = distance;
    sfml->game->rays[ray_id].angle = angle;
}

static void determine_wall_hit(sfml_t *sfml, wall_hit_data_t data)
{
    if (data.vert_dist < data.horz_dist)
        calculate_wall_hit_from_vertical(sfml, data.ray_angle, data.ray_id);
    else
        calculate_wall_hit_from_horizontal(sfml, data.ray_angle, data.ray_id);
}

static void process_single_ray(sfml_t *sfml, float ray_angle, int ray_id)
{
    float horz_dist = calculate_horizontal_distance(sfml, ray_angle);
    float vert_dist = calculate_vertical_distance(sfml, ray_angle);
    float distance = get_min_distance(horz_dist, vert_dist);

    set_ray_data(sfml, ray_id, distance, ray_angle);
    determine_wall_hit(sfml,
        (wall_hit_data_t){ray_angle, ray_id, horz_dist, vert_dist});
}

void calculate_wall_hit(sfml_t *sfml, float ray_angle, int ray_id)
{
    float horz_dist = calculate_horizontal_distance(sfml, ray_angle);
    float vert_dist = calculate_vertical_distance(sfml, ray_angle);

    determine_wall_hit(sfml,
        (wall_hit_data_t){ray_angle, ray_id, horz_dist, vert_dist});
}

void cast_ray(sfml_t *sfml, float ray_angle, int ray_id)
{
    ray_angle = normalize_angle(ray_angle);
    process_single_ray(sfml, ray_angle, ray_id);
}
