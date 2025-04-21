/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** init.c
*/

#include "wolf3d.h"

void init_sfml(sfml_t *sfml)
{
    srand(time(NULL));
    init_window(sfml);
    init_game(sfml);
    init_clock(sfml);
    init_map(sfml);
    init_music(sfml);
}
