/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** free_music.c
*/

#include "wolf3d.h"

void free_music(sfml_t *sfml)
{
    if (!sfml->music)
        return;
    if (sfml->music->music) {
        sfMusic_destroy(sfml->music->music);
        sfml->music->music = NULL;
    }
    if (sfml->music->menu_music) {
        sfMusic_destroy(sfml->music->menu_music);
        sfml->music->menu_music = NULL;
    }
    free(sfml->music);
    sfml->music = NULL;
}
