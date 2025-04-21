/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** free_hud.c
*/

#include "wolf3d.h"

void free_hud(sfml_t *sfml)
{
    sfSprite_destroy(sfml->game->hud->doom_guy);
    sfml->game->hud->doom_guy = NULL;
    sfSprite_destroy(sfml->game->hud->stbar);
    sfml->game->hud->stbar = NULL;
    sfTexture_destroy(sfml->game->hud->stbar_texture);
    sfml->game->hud->stbar_texture = NULL;
    sfTexture_destroy(sfml->game->hud->doom_guy_texture);
    sfml->game->hud->doom_guy_texture = NULL;
    free(sfml->game->hud);
    sfml->game->hud = NULL;
}
