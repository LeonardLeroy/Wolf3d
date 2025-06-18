/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** free_cameras.c
*/

#include "wolf3d.h"

void free_cameras(sfml_t *sfml)
{
    if (!sfml->game->cameras)
        return;
    if (sfml->game->cameras->camGame) {
        sfView_destroy(sfml->game->cameras->camGame);
        sfml->game->cameras->camGame = NULL;
    }
    if (sfml->game->cameras->camHUD) {
        sfView_destroy(sfml->game->cameras->camHUD);
        sfml->game->cameras->camHUD = NULL;
    }
    if (sfml->game->cameras->camMenu) {
        sfView_destroy(sfml->game->cameras->camMenu);
        sfml->game->cameras->camMenu = NULL;
    }
    free(sfml->game->cameras);
    sfml->game->cameras = NULL;
}
