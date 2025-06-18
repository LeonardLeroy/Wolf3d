/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** free_hud.c
*/

#include "wolf3d.h"

static void free_hud_sprites(hud_t *hud)
{
    if (hud->doom_guy) {
        sfSprite_destroy(hud->doom_guy);
        hud->doom_guy = NULL;
    }
    if (hud->stbar) {
        sfSprite_destroy(hud->stbar);
        hud->stbar = NULL;
    }
}

static void free_hud_textures(hud_t *hud)
{
    if (hud->doom_guy_texture) {
        sfTexture_destroy(hud->doom_guy_texture);
        hud->doom_guy_texture = NULL;
    }
    if (hud->stbar_texture) {
        sfTexture_destroy(hud->stbar_texture);
        hud->stbar_texture = NULL;
    }
}

void free_hud(sfml_t *sfml)
{
    if (!sfml->game->hud)
        return;
    free_hud_sprites(sfml->game->hud);
    free_hud_textures(sfml->game->hud);
    free(sfml->game->hud);
    sfml->game->hud = NULL;
}
