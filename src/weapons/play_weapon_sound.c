/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** play_weapon_sound.c
*/

#include "wolf3d.h"

void play_weapon_sound(sfml_t *sfml, enum WEAPONS weapon)
{
    switch (weapon) {
        case SHOTGUN:
            play_sound(sfml, "shotgun", 100);
            break;
        case SUPER_SHOTGUN:
            play_sound(sfml, "super_shotgun", 100);
            break;
        default:
            play_sound(sfml, "pistol", 100);
            break;
    }
}
