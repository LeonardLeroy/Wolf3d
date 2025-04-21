/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** is_ray_facing.c
*/

#include "wolf3d.h"

int is_ray_facing_down(float angle)
{
    return angle > 0 && angle < PI;
}

int is_ray_facing_up(float angle)
{
    return !is_ray_facing_down(angle);
}

int is_ray_facing_right(float angle)
{
    return angle < 0.5 * PI || angle > 1.5 * PI;
}

int is_ray_facing_left(float angle)
{
    return !is_ray_facing_right(angle);
}
