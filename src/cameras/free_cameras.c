/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** free_cameras.c
*/

#include "wolf3d.h"

void free_cameras(sfml_t *sfml)
{
    sfView_destroy(sfml->game->cameras->camGame);
    sfml->game->cameras->camGame = NULL;
    sfView_destroy(sfml->game->cameras->camHUD);
    sfml->game->cameras->camHUD = NULL;
    free(sfml->game->cameras);
    sfml->game->cameras = NULL;
}
