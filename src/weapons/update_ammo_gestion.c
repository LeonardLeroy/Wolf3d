/*
** EPITECH PROJECT, 2024
** wolf3d
** File description:
** update_ammo_gestion.c
*/

#include "wolf3d.h"

static int handle_bullets_ammo(player_t *player)
{
    if (player->ammo.bullets > 0) {
        player->ammo.bullets--;
        return (1);
    }
    return (0);
}

static int handle_shells_ammo(player_t *player)
{
    if (player->ammo.shells > 0) {
        player->ammo.shells--;
        return (1);
    }
    return (0);
}

int handle_ammo(player_t *player, weapon_t *weapon)
{
    switch (weapon->type) {
        case PISTOL:
        case SHOTGUN:
        case SUPER_SHOTGUN:
        case CHAINGUN:
            return handle_ammo_by_type(player, weapon->type);
        default:
            return (1);
    }
}

int handle_ammo_by_type(player_t *player, int weapon_type)
{
    switch (weapon_type) {
        case PISTOL:
        case CHAINGUN:
            return (handle_bullets_ammo(player));
        case SHOTGUN:
        case SUPER_SHOTGUN:
            return (handle_shells_ammo(player));
        default:
            return (0);
    }
}
