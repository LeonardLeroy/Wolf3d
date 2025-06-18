/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** enemy_grunt.c
*/

#include "wolf3d.h"

static char *get_enemy_grunt_sound(int type)
{
    switch (type) {
        case IMP:
            return "imp";
        default:
            return "zombie";
    }
}

void enemy_grunt(sfml_t *sfml, enemy_t *enemy)
{
    if (enemy->current != enemy->walk)
        return;
    if (rand() % 1000 == 0)
        play_sound(sfml, get_enemy_grunt_sound(enemy->type), 60);
}
