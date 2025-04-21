/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** init_rays.c
*/

#include "wolf3d.h"

void init_rays(ray_t *ray)
{
    ray->was_hit_vertical = 0;
    ray->wall_hit_content = 0;
    ray->distance = 0;
    ray->angle = 0;
    ray->wall_hit_x = 0;
    ray->wall_hit_y = 0;
}
