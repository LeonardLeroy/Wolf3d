/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** cast_ray_vertical.c
*/

#include "wolf3d.h"

static float calculate_y_intercept(sfml_t *sfml, float ray_angle,
    float xintercept)
{
    float xdist = xintercept - sfml->game->player->x;

    return (xdist * tan(ray_angle)) + sfml->game->player->y;
}

static void calculate_vertical_steps(float ray_angle, float *xstep,
    float *ystep)
{
    float tan_a = tan(ray_angle);

    *xstep = TILE_SIZE;
    if (is_ray_facing_left(ray_angle))
        *xstep = -(*xstep);
    *ystep = TILE_SIZE * tan_a;
    if ((is_ray_facing_up(ray_angle) && *ystep > 0) ||
        (is_ray_facing_down(ray_angle) && *ystep < 0))
        *ystep = -(*ystep);
}

static void set_vertical_intercepts(sfml_t *sfml, float ray_angle,
    float *xintercept, float *yintercept)
{
    *xintercept = sfml->game->player->x / TILE_SIZE;
    *xintercept = floor(*xintercept) * TILE_SIZE;
    if (is_ray_facing_right(ray_angle))
        *xintercept += TILE_SIZE;
    *yintercept = calculate_y_intercept(sfml, ray_angle, *xintercept);
}

static float check_vertical_collision(sfml_t *sfml, collision_check_t check)
{
    if (is_wall(sfml, check.check_x, check.check_y)) {
        return calculate_actual_distance(sfml->game->player->x,
            sfml->game->player->y,
            check.next_x, check.next_y);
    }
    return -1;
}

static void init_vertical_ray_data(sfml_t *sfml, float ray_angle,
    ray_data_t *data)
{
    set_vertical_intercepts(sfml, ray_angle, &data->xintercept,
        &data->yintercept);
    calculate_vertical_steps(ray_angle, &data->xstep, &data->ystep);
    init_next_coordinates(data->xintercept, data->yintercept,
        &data->next_x, &data->next_y);
}

float calculate_vertical_distance(sfml_t *sfml, float ray_angle)
{
    ray_data_t data;
    float check_x;
    float check_y;
    float dist;

    init_vertical_ray_data(sfml, ray_angle, &data);
    while (is_within_bounds(data.next_x, data.next_y)) {
        adjust_for_ray_direction(ray_angle, data.next_x, &check_x, 1);
        check_y = data.next_y;
        dist = check_vertical_collision(sfml,
            (collision_check_t){check_x, check_y,
            data.next_x, data.next_y});
        if (dist >= 0)
            return dist;
        data.next_x += data.xstep;
        data.next_y += data.ystep;
    }
    return FLT_MAX;
}

void calculate_wall_hit_from_vertical(sfml_t *sfml, float ray_angle,
    int ray_id)
{
    ray_data_t data;
    float check_x;
    float check_y;

    init_vertical_ray_data(sfml, ray_angle, &data);
    while (is_within_bounds(data.next_x, data.next_y)) {
        adjust_for_ray_direction(ray_angle, data.next_x, &check_x, 0);
        check_y = data.next_y;
        if (check_wall_hit(sfml,
            (collision_check_t){check_x, check_y, data.next_x, data.next_y},
            ray_id))
            break;
        data.next_x += data.xstep;
        data.next_y += data.ystep;
    }
}
