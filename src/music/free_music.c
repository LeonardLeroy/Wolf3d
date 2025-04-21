/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** free_music.c
*/

#include "wolf3d.h"

void free_music(sfml_t *sfml)
{
    sfMusic_destroy(sfml->music);
    sfml->music = NULL;
}
