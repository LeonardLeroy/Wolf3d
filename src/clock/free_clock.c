/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** free_clock.c
*/

#include "wolf3d.h"

void free_clock(sfml_t *sfml)
{
    if (!sfml->clocks)
        return;
    if (sfml->clocks->clock)
        sfClock_destroy(sfml->clocks->clock);
    free(sfml->clocks);
    sfml->clocks = NULL;
}
