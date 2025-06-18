/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** switch_weapon.c
*/

#include "wolf3d.h"

void switch_weapon(sfml_t *sfml, int switch_index)
{
    static int current_weapon = 1;

    if (sfml->game->game_substate != NORMAL || switch_index == current_weapon)
        return;
    sfml->game->player->weapon->sheet->anim_timer = 0.0f;
    set_current_frame(sfml->game->player->weapon->sheet, 0);
    current_weapon = switch_index;
    if (current_weapon < 0)
        current_weapon = WEAPONS_AMOUNT - 1;
    if (current_weapon >= WEAPONS_AMOUNT)
        current_weapon = 0;
    sfml->game->player->weapon = sfml->game->weapons[current_weapon];
}
