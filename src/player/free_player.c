/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** free_player.c
*/

#include "wolf3d.h"

void free_player(sfml_t *sfml)
{
    if (!sfml->game->player)
        return;
    free(sfml->game->player);
    sfml->game->player = NULL;
}
