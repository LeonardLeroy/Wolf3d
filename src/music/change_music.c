/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** change_music.c
*/

#include "wolf3d.h"

void change_music(sfml_t *sfml, sfMusic *music)
{
    sfMusic_stop(sfml->music->current);
    sfml->music->current = music;
    sfMusic_play(sfml->music->current);
}
