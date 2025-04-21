/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** free.c
*/

#include "wolf3d.h"

void free_sfml(sfml_t *sfml)
{
    free_game(sfml);
    free_music(sfml);
    free_clock(sfml);
    free_window(sfml);
}
