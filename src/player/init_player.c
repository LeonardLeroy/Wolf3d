/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** init_player.c
*/

#include "wolf3d.h"

void init_player(sfml_t *sfml)
{
    sfml->game->player = salloc(sizeof(player_t));
    memset(sfml->game->player, 0, sizeof(player_t));
    sfml->game->player->x = TILE_SIZE + TILE_SIZE / 2;
    sfml->game->player->y = TILE_SIZE + TILE_SIZE / 2;
    sfml->game->player->angle = PI / 2;
    sfml->game->player->hp = 100;
    sfml->game->player->frags = 0;
    sfml->game->player->ammo.bullets = 150;
    sfml->game->player->ammo.shells = 16;
    sfml->game->player->weapon = NULL;
    sfml->game->player->flashlight_active = 0;
    sfml->game->player->muzzle_flash_timer = 0.0f;
}
