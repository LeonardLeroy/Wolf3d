/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** update_sprite.c
*/

#include "wolf3d.h"

void update_skull(sfml_t *sfml, sprite_sheet_t *sheet)
{
    static float anim_timer = 0.0f;
    static const float anim_delay = GAME_TIC * 24;

    anim_timer += sfml->clocks->deltaTime;
    if (anim_timer >= anim_delay) {
        set_current_frame(sheet, sheet->current_frame == 1 ? 0 : 1);
        anim_timer -= anim_delay;
    }
}
