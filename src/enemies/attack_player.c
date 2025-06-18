/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** attack_player.c
*/

#include "wolf3d.h"

static float get_distance_from_enemy(enemy_t *enemy)
{
    switch (enemy->type) {
        case IMP:
            return 50.0f;
        default:
            return 300.0f;
    }
}

static int get_chances_from_enemy(enemy_t *enemy)
{
    switch (enemy->type) {
        case IMP:
            return 8;
        default:
            return 48;
    }
}

static char *get_enemy_shoot_sound(enemy_t *enemy)
{
    switch (enemy->type) {
        case IMP:
            return "claw";
        default:
            return "pistol";
    }
}

void handle_enemy_attack(sfml_t *sfml, enemy_t *enemy)
{
    if (enemy->shoot->current_frame == enemy->shoot->frames - 1) {
        enemy->current = enemy->walk;
        enemy->shoot->anim_timer = 0.0f;
        set_current_frame(enemy->current, 0);
        return;
    }
    if (enemy->shoot->current_frame == 4 && rand() % 4 == 0) {
        sfml->game->player->hp -= rand() % 6 + 5;
        if (sfml->game->player->hp <= 0) {
            sfml->game->player->hp = 0;
            game_over(sfml);
            return;
        }
        play_sound(sfml, "pain", 75);
        set_doomguy_face(sfml, 4);
    }
}

void attack_player(sfml_t *sfml, enemy_t *enemy)
{
    if (enemy->current != enemy->shoot && calculate_enemy_distance(enemy,
        sfml->game->player) <= get_distance_from_enemy(enemy) &&
        rand() % get_chances_from_enemy(enemy) == 0) {
        enemy->current = enemy->shoot;
        play_sound(sfml, get_enemy_shoot_sound(enemy), 75);
        enemy->current->anim_timer = 0.0f;
        set_current_frame(enemy->current, 0);
    }
}
