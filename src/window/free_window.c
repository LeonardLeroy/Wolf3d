/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** free_window.c
*/

#include "wolf3d.h"

void free_window_size(sfml_t *sfml)
{
    if (!sfml->window_size)
        return;
    free(sfml->window_size);
    sfml->window_size = NULL;
}

void free_window(sfml_t *sfml)
{
    sfRenderWindow_destroy(sfml->window);
    sfml->window = NULL;
}
