/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** init_music.c
*/

#include "wolf3d.h"

void init_music(sfml_t *sfml)
{
    sfml->music = sfMusic_createFromFile(music("E1M1"));
    sfMusic_setLoop(sfml->music, 1);
    sfMusic_setVolume(sfml->music, 25);
    sfMusic_play(sfml->music);
}
