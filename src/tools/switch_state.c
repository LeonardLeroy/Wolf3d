/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** switch_state.c
*/

#include "wolf3d.h"

void switch_state(sfml_t *sfml, switch_state_args_t args)
{
    sfml->update_f = args.update;
    sfml->events_f = args.events;
    sfml->state = args.state;
}

void switch_menu_substate(sfml_t *sfml, switch_menu_substate_args_t args)
{
    sfml->update_f = args.update;
    sfml->events_f = args.events;
    sfml->menu->menu_substate = args.substate;
}
