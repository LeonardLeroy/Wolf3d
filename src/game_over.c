/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** game_over.c
*/

#include "wolf3d.h"

void game_over(sfml_t *sfml)
{
    play_sound(sfml, rand() % 2 == 0 ? "death1" : "death2", 100);
    trigger_game_lose(sfml);
}
