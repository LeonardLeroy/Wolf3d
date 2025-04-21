/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** normalize_angle.c
*/

#include "wolf3d.h"

float normalize_angle(float angle)
{
    angle = fmod(angle, 2 * PI);
    if (angle < 0)
        angle += 2 * PI;
    return angle;
}
