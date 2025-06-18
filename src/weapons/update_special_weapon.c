/*
** EPITECH PROJECT, 2024
** wolf3d
** File description:
** update_special_weapon.c
*/

#include "wolf3d.h"

static void handle_fist_anim(sfml_t *sfml, weapon_t *weapon)
{
    int new_current_frame = weapon->sheet->current_frame + 1;

    if (weapon->sheet->anim_timer >= FRAME_DURATION) {
        if (new_current_frame >= weapon->sheet->frames)
            new_current_frame = 1;
        set_current_frame(weapon->sheet, new_current_frame);
        if (new_current_frame == 2)
            play_sound(sfml, "fist_swing", 100);
        if (new_current_frame == 4) {
            play_sound(sfml, "punch", 100);
            play_weapon_particle(sfml, 0);
        }
        weapon->sheet->anim_timer -= FRAME_DURATION;
    }
}

static void handle_chaingun_anim(sfml_t *sfml, weapon_t *weapon)
{
    int can_shoot = 0;

    if (weapon->sheet->anim_timer >= FRAME_DURATION) {
        can_shoot = handle_ammo(sfml->game->player, weapon);
        if (!can_shoot) {
            weapon->sheet->anim_timer = 0.0f;
            set_current_frame(weapon->sheet, 0);
            return;
        }
        set_current_frame(weapon->sheet,
            weapon->sheet->current_frame == 1 ? 2 : 1);
        play_weapon_sound(sfml, sfml->game->player->weapon->type);
        play_weapon_particle(sfml, 0);
        trigger_muzzle_flash(sfml);
        weapon->sheet->anim_timer -= FRAME_DURATION;
    }
}

int handle_special_weapons(sfml_t *sfml, weapon_t *weapon)
{
    switch (weapon->type) {
        case CHAINGUN:
            handle_chaingun_anim(sfml, weapon);
            return (1);
        case FIST:
            handle_fist_anim(sfml, weapon);
            return (1);
        default:
            return (0);
    }
}
