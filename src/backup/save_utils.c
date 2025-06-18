/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-evan.lafolie
** File description:
** save_utils.c
*/

#include "wolf3d.h"

const char *weapon_type_to_string(enum WEAPONS type)
{
    switch (type) {
        case FIST:
            return "FIST";
        case PISTOL:
            return "PISTOL";
        case SHOTGUN:
            return "SHOTGUN";
        case SUPER_SHOTGUN:
            return "SUPER_SHOTGUN";
        case CHAINGUN:
            return "CHAINGUN";
        default:
            return "UNKNOWN";
    }
}
