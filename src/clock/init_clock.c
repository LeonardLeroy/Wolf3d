/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** init_clock.c
*/

#include "wolf3d.h"

void init_clock(sfml_t *sfml)
{
    sfml->clock = sfClock_create();
}
