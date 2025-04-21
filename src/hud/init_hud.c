/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** init_hud.c
*/

#include "wolf3d.h"

void init_stbar(sfml_t *sfml)
{
    sfVector2u texture_size;
    float scale_factor;
    sfVector2u window_size = sfRenderWindow_getSize(sfml->window);

    sfml->game->hud->stbar_texture = sfTexture_createFromFile(image("stbar"),
        NULL);
    sfml->game->hud->stbar = sfSprite_create();
    sfSprite_setTexture(sfml->game->hud->stbar, sfml->game->hud->stbar_texture,
        sfTrue);
    texture_size = sfTexture_getSize(sfml->game->hud->stbar_texture);
    scale_factor = (float)window_size.x / texture_size.x;
    sfSprite_setScale(sfml->game->hud->stbar, (sfVector2f){scale_factor,
        scale_factor});
    sfSprite_setPosition(sfml->game->hud->stbar,
        (sfVector2f){0, window_size.y - texture_size.y * scale_factor});
}

void init_doom_guy(sfml_t *sfml)
{
    sfVector2u texture_size;
    float scale_factor;
    sfVector2u face_size;
    sfVector2u window_size = sfRenderWindow_getSize(sfml->window);

    sfml->game->hud->doom_guy_texture =
    sfTexture_createFromFile(image("doomguy"), NULL);
    sfml->game->hud->doom_guy = sfSprite_create();
    sfSprite_setTexture(sfml->game->hud->doom_guy,
        sfml->game->hud->doom_guy_texture, sfTrue);
    face_size = sfTexture_getSize(sfml->game->hud->doom_guy_texture);
    texture_size = sfTexture_getSize(sfml->game->hud->stbar_texture);
    scale_factor = (float)window_size.x / texture_size.x;
    sfSprite_setScale(sfml->game->hud->doom_guy,
        (sfVector2f){scale_factor, scale_factor});
    sfSprite_setPosition(sfml->game->hud->doom_guy, (sfVector2f){
            window_size.x / 2 - (face_size.x * scale_factor) / 2,
            window_size.y - texture_size.y * scale_factor +
            (texture_size.y * scale_factor - face_size.y * scale_factor) / 2
        });
}

void init_hud(sfml_t *sfml)
{
    sfml->game->hud = salloc(sizeof(hud_t));
    init_stbar(sfml);
    init_doom_guy(sfml);
}
