/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** free_game.c
*/

#include "wolf3d.h"

void free_game(sfml_t *sfml)
{
    free_cameras(sfml);
    free_player(sfml);
    free_hud(sfml);
    free(sfml->game->rays);
    sfml->game->rays = NULL;
    free(sfml->game);
    sfml->game = NULL;
}
