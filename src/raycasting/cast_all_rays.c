/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** cast_all_rays.c
*/

#include "wolf3d.h"

void cast_all_rays(sfml_t *sfml)
{
    float ray_angle = sfml->game->player->angle - (FOV / 2);

    for (int i = 0; i < NUM_RAYS; i++) {
        cast_ray(sfml, ray_angle, i);
        ray_angle += FOV / NUM_RAYS;
    }
}
