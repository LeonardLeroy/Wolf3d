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
    sfml->state = MENU;
    init_cursor(sfml);
    init_sounds(sfml);
    init_fonts(sfml);
    init_game(sfml);
    init_menu(sfml);
    init_clock(sfml);
    init_music(sfml);
    init_transition(sfml);
    init_win_lose(sfml);
    sfml->update_f = &update_menu;
    sfml->events_f = &events_menu;
}
