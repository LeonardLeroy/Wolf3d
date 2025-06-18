/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** update_enemy_anims.c
*/

#include "wolf3d.h"

void update_enemy_anims(enemy_t *enemy)
{
    if (enemy->current == enemy->hurt) {
        if (enemy->current->current_frame == enemy->current->frames - 1) {
            enemy->current = enemy->walk;
            enemy->current->anim_timer = 0.0f;
            set_current_frame(enemy->current, 0);
            return;
        }
    }
    set_current_frame(enemy->current,
        (enemy->current->current_frame == enemy->current->frames - 1) ? 0
            : enemy->current->current_frame + 1);
}
