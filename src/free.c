/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** free.c
*/

#include "wolf3d.h"

void free_sfml(sfml_t *sfml)
{
    free_transition(sfml);
    free_weapons(sfml);
    free_game(sfml);
    free_menu(sfml);
    free_music(sfml);
    free_clock(sfml);
    free_sounds(sfml);
    free_fonts(sfml);
    free_cursor(sfml);
    free_window_size(sfml);
    free_window(sfml);
    free_win_lose(sfml);
}
