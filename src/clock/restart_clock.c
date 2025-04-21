/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** restart_clock.c
*/

#include "wolf3d.h"

void restart_clock(sfml_t *sfml)
{
    sfClock_restart(sfml->clock);
}
