/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** update_weapon.c
*/

#include "wolf3d.h"

void update_weapon(sfml_t *sfml, weapon_t *weapon)
{
    if (!weapon->shooting) {
        set_current_frame(weapon->sheet, 0);
        weapon->sheet->anim_timer = 0.0f;
        return;
    }
    weapon->sheet->anim_timer += sfml->clocks->deltaTime;
    if (handle_special_weapons(sfml, weapon))
        return;
    if (weapon->sheet->anim_timer >= FRAME_DURATION) {
        set_current_frame(weapon->sheet, weapon->sheet->current_frame + 1);
        weapon->sheet->anim_timer -= FRAME_DURATION;
        if (weapon->sheet->current_frame == weapon->sheet->frames - 1)
            weapon->shooting = 0;
    }
}

static void make_particles_from_weapon(sfml_t *sfml, weapon_t *weapon)
{
    int i = 0;

    if (weapon->type == SHOTGUN) {
        for (; i < 7; i++)
            play_weapon_particle(sfml, i);
    }
    if (weapon->type == SUPER_SHOTGUN) {
        for (; i < 20; i++)
            play_weapon_particle(sfml, i);
    }
    play_weapon_particle(sfml, i);
}

void handle_weapon_anim(sfml_t *sfml, weapon_t *weapon)
{
    if (sfml->game->player->weapon->shooting ||
        sfml->game->player->weapon->sheet->current_frame != 0)
        return;
    sfml->game->player->weapon->shooting = 1;
    if (weapon->type != FIST)
        sfml->game->player->muzzle_flash_timer = MUZZLE_FLASH_DURATION;
    if ((sfml->game->player->weapon->type == CHAINGUN ||
        sfml->game->player->weapon->type == FIST)) {
        sfml->game->player->weapon->sheet->anim_timer = FRAME_DURATION;
        update_weapon(sfml, sfml->game->player->weapon);
    } else {
        make_particles_from_weapon(sfml, weapon);
        play_weapon_sound(sfml, weapon->type);
    }
}

void handle_shooting(sfml_t *sfml)
{
    player_t *player = sfml->game->player;
    weapon_t *weapon = player->weapon;
    int can_shoot = 0;

    if (weapon->shooting)
        return;
    if (weapon->sheet->current_frame != 0)
        return;
    can_shoot = handle_ammo(player, weapon);
    if (!can_shoot)
        return;
    handle_weapon_anim(sfml, weapon);
}

void handle_release_shooting(sfml_t *sfml, int *stop_firing_requested)
{
    if (sfml->game->player->weapon->shooting) {
        if (sfml->game->player->weapon->type == CHAINGUN)
            sfml->game->player->weapon->shooting = 0;
        if (sfml->game->player->weapon->type == FIST)
            *stop_firing_requested = 1;
    }
}
