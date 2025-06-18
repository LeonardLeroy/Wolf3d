/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** init_clock.c
*/

#include "wolf3d.h"

void init_clock(sfml_t *sfml)
{
    sfml->clocks = salloc(sizeof(clocks_t));
    sfml->clocks->clock = sfClock_create();
    sfml->clocks->deltaTime = 0.0f;
    sfml->clocks->elapsed = 0.0f;
}
