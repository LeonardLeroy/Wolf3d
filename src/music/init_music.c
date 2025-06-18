/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** init_music.c
*/

#include "wolf3d.h"

void init_music(sfml_t *sfml)
{
    sfml->music = salloc(sizeof(music_t));
    sfml->music->menu_music = sfMusic_createFromFile(music("intro"));
    sfml->music->music = sfMusic_createFromFile(music("doom_type_shi"));
    sfml->music->current = sfml->music->menu_music;
    sfMusic_setLoop(sfml->music->music, 1);
    sfMusic_setVolume(sfml->music->music, 50);
    sfMusic_setVolume(sfml->music->menu_music, 50);
    sfMusic_play(sfml->music->menu_music);
}
