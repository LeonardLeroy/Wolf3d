/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** update_clock.c
*/

#include "wolf3d.h"

void update_clock(sfml_t *sfml)
{
    sfml->clocks->deltaTime = sfTime_asSeconds(
        sfClock_getElapsedTime(sfml->clocks->clock));
    sfml->clocks->elapsed += sfml->clocks->deltaTime;
    sfClock_restart(sfml->clocks->clock);
}
