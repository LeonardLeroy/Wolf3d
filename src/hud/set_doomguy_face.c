/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** set_doomguy_face.c
*/

#include "wolf3d.h"

int check_doomguy_sprite_row(sfml_t *sfml)
{
    float hp = sfml->game->player->hp;

    if (hp <= 20)
        return 4;
    if (hp <= 40)
        return 3;
    if (hp <= 60)
        return 2;
    if (hp <= 80)
        return 1;
    return 0;
}

void set_doomguy_face(sfml_t *sfml, int column)
{
    if (column == 0) {
        regular_doom_face(sfml);
        return;
    }
    sfml->game->hud->doomguy_face_row = check_doomguy_sprite_row(sfml);
    sfSprite_setTextureRect(sfml->game->hud->doom_guy, (sfIntRect)
        {column * 32, sfml->game->hud->doomguy_face_row * 32, 32, 32});
    sfml->game->hud->doomguy_anim_clock = 0;
}
