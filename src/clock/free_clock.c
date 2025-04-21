/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** free_clock.c
*/

#include "wolf3d.h"

void free_clock(sfml_t *sfml)
{
    sfClock_destroy(sfml->clock);
}
