/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** events.c
*/

#include "wolf3d.h"

void events(sfml_t *sfml)
{
    if (sfml->event.type == sfEvtClosed)
        sfRenderWindow_close(sfml->window);
    if (sfml->event.type == sfEvtResized)
        handle_window_resize(sfml);
    sfml->events_f(sfml);
}
