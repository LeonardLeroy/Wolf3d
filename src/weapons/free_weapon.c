/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** free_weapon.c
*/

#include "wolf3d.h"

void free_weapon(weapon_t *weapon)
{
    if (!weapon)
        return;
    if (weapon->sheet) {
        free_sprite_sheet(weapon->sheet);
        weapon->sheet = NULL;
    }
    free(weapon);
    weapon = NULL;
}

void free_weapons(sfml_t *sfml)
{
    if (!sfml->game->weapons)
        return;
    if (sfml->game->player->weapon)
        sfml->game->player->weapon = NULL;
    for (enum WEAPONS i = 0; i < WEAPONS_AMOUNT; i++) {
        if (!sfml->game->weapons[i])
            continue;
        free_weapon(sfml->game->weapons[i]);
    }
    free(sfml->game->weapons);
    sfml->game->weapons = NULL;
}
