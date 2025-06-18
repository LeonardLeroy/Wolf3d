/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** muzzle_flash.c
*/

#include "wolf3d.h"

void trigger_muzzle_flash(sfml_t *sfml)
{
    if (!sfml->game->player)
        return;
    if (sfml->game->player->weapon->type == FIST)
        return;
    sfml->game->player->muzzle_flash_timer = MUZZLE_FLASH_DURATION;
}

void update_muzzle_flash(sfml_t *sfml)
{
    if (!sfml->game->player)
        return;
    if (sfml->game->player->muzzle_flash_timer > 0) {
        sfml->game->player->muzzle_flash_timer -= sfml->clocks->deltaTime;
        if (sfml->game->player->muzzle_flash_timer < 0)
            sfml->game->player->muzzle_flash_timer = 0;
    }
}
