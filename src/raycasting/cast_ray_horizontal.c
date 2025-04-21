/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** Horizontal ray casting
*/

#include "wolf3d.h"

static float calculate_x_intercept(sfml_t *sfml, float ray_angle,
    float yintercept)
{
    float ydist = yintercept - sfml->game->player->y;
    float tan_a = tan(ray_angle);

    return (ydist / tan_a) + sfml->game->player->x;
}

static void calculate_steps(float ray_angle, float *xstep, float *ystep)
{
    float tan_a = tan(ray_angle);

    *ystep = TILE_SIZE;
    if (is_ray_facing_up(ray_angle))
        *ystep = -(*ystep);
    *xstep = TILE_SIZE / tan_a;
    if ((is_ray_facing_left(ray_angle) && *xstep > 0) ||
        (is_ray_facing_right(ray_angle) && *xstep < 0)) {
        *xstep = -(*xstep);
    }
}

static void set_horizontal_intercepts(sfml_t *sfml, float ray_angle,
    float *xintercept, float *yintercept)
{
    *yintercept = sfml->game->player->y / TILE_SIZE;
    *yintercept = floor(*yintercept) * TILE_SIZE;
    if (is_ray_facing_down(ray_angle))
        *yintercept += TILE_SIZE;
    *xintercept = calculate_x_intercept(sfml, ray_angle, *yintercept);
}

static float check_horizontal_collision(sfml_t *sfml, collision_check_t check)
{
    if (is_wall(sfml, check.check_x, check.check_y)) {
        return calculate_actual_distance(sfml->game->player->x,
            sfml->game->player->y,
            check.next_x, check.next_y);
    }
    return -1;
}

static void init_horizontal_ray_data(sfml_t *sfml, float ray_angle,
    ray_data_t *data)
{
    set_horizontal_intercepts(sfml, ray_angle, &data->xintercept,
        &data->yintercept);
    calculate_steps(ray_angle, &data->xstep, &data->ystep);
    init_next_coordinates(data->xintercept, data->yintercept,
        &data->next_x, &data->next_y);
}

float calculate_horizontal_distance(sfml_t *sfml, float ray_angle)
{
    ray_data_t data;
    float check_x;
    float check_y;
    float dist;

    init_horizontal_ray_data(sfml, ray_angle, &data);
    while (is_within_bounds(data.next_x, data.next_y)) {
        check_x = data.next_x;
        check_y = data.next_y;
        if (is_ray_facing_up(ray_angle))
            check_y -= 1;
        dist = check_horizontal_collision(sfml,
            (collision_check_t){check_x, check_y,
            data.next_x, data.next_y});
        if (dist >= 0)
            return dist;
        data.next_x += data.xstep;
        data.next_y += data.ystep;
    }
    return FLT_MAX;
}

void calculate_wall_hit_from_horizontal(sfml_t *sfml, float ray_angle,
    int ray_id)
{
    ray_data_t data;
    float check_x;
    float check_y;

    init_horizontal_ray_data(sfml, ray_angle, &data);
    while (is_within_bounds(data.next_x, data.next_y)) {
        adjust_for_ray_direction(ray_angle, data.next_y, &check_y, 0);
        check_x = data.next_x;
        if (check_wall_hit(sfml,
            (collision_check_t){check_x, check_y, data.next_x, data.next_y},
            ray_id))
            break;
        data.next_x += data.xstep;
        data.next_y += data.ystep;
    }
}
