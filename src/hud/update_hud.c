/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** update_hud.c
*/

#include "wolf3d.h"

void regular_doom_face(sfml_t *sfml)
{
    int column = rand() % 3;
    int row;

    sfml->game->hud->doomguy_face_row = check_doomguy_sprite_row(sfml);
    row = sfml->game->hud->doomguy_face_row;
    sfSprite_setTextureRect(sfml->game->hud->doom_guy,
        (sfIntRect){column * 32, row * 32, 32, 32});
    sfml->game->hud->doomguy_anim_clock = 0;
}

void update_doomguy_face(sfml_t *sfml, hud_t *hud)
{
    hud->doomguy_anim_clock += sfml->clocks->deltaTime;
    if (hud->doomguy_anim_clock >= FRAME_DURATION * 4) {
        if (sfml->game->hud->doomguy_face_column >= 4) {
            sfml->game->hud->doomguy_face_column = 0;
            regular_doom_face(sfml);
            return;
        }
        if (rand() % 2 == 0)
            regular_doom_face(sfml);
        hud->doomguy_anim_clock = 0;
    }
}

void update_hud(sfml_t *sfml)
{
    hud_t *hud = sfml->game->hud;

    if (sfml->game->player->hp <= 0)
        return;
    update_doomguy_face(sfml, hud);
}
