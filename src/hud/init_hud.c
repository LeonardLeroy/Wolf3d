/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** init_hud.c
*/

#include "wolf3d.h"

static float get_scale_factor_hud(sfRenderWindow *window, sfTexture *texture)
{
    sfVector2u window_size = sfRenderWindow_getSize(window);
    sfVector2u texture_size = sfTexture_getSize(texture);

    return ((float) window_size.x / texture_size.x);
}

sfVector2f get_stbar_position(sfRenderWindow *window,
    sfTexture *texture, float scale)
{
    sfVector2u window_size = sfRenderWindow_getSize(window);
    sfVector2u texture_size = sfTexture_getSize(texture);

    return ((sfVector2f){0, window_size.y - texture_size.y * scale});
}

static sfVector2f get_doomguy_position(sfRenderWindow *window,
    sfTexture *stbar_tex, float scale)
{
    sfVector2u window_size = sfRenderWindow_getSize(window);
    sfVector2u stbar_size = sfTexture_getSize(stbar_tex);
    float x = window_size.x / 2.0f - (32 * scale) / 2.0f;
    float y = window_size.y - stbar_size.y * scale
        + (stbar_size.y * scale - 32 * scale) / 2.0f;

    return ((sfVector2f){x, y});
}

void init_stbar(sfml_t *sfml)
{
    sfTexture *texture = sfTexture_createFromFile(image("hud/stbar"), NULL);
    sfSprite *sprite = sfSprite_create();
    float scale = get_scale_factor_hud(sfml->window, texture);
    sfVector2f pos = get_stbar_position(sfml->window, texture, scale);

    sfSprite_setTexture(sprite, texture, sfTrue);
    sfSprite_setScale(sprite, (sfVector2f){scale, scale});
    sfSprite_setPosition(sprite, pos);
    sfml->game->hud->stbar_texture = texture;
    sfml->game->hud->stbar = sprite;
}

void init_doomguy(sfml_t *sfml)
{
    sfTexture *texture = sfTexture_createFromFile(image("hud/doom_sprite"),
        NULL);
    sfSprite *sprite = sfSprite_create();
    float scale = (sfRenderWindow_getSize(sfml->window).x / 1280.0f) * 3.8f;
    sfVector2f pos = get_doomguy_position(sfml->window,
        sfml->game->hud->stbar_texture, scale);

    sfSprite_setTexture(sprite, texture, sfTrue);
    sfSprite_setScale(sprite, (sfVector2f){scale, scale});
    sfSprite_setPosition(sprite, pos);
    sfml->game->hud->doom_guy_texture = texture;
    sfml->game->hud->doom_guy = sprite;
    sfml->game->hud->doomguy_face_row = check_doomguy_sprite_row(sfml);
    sfSprite_setTextureRect(sfml->game->hud->doom_guy,
        (sfIntRect){0, sfml->game->hud->doomguy_face_row * 32, 32, 32});
}

void init_hud(sfml_t *sfml)
{
    sfml->game->hud = salloc(sizeof(hud_t));
    memset(sfml->game->hud, 0, sizeof(hud_t));
    init_stbar(sfml);
    init_doomguy(sfml);
}
