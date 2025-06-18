/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** normalize_angle_range.c
*/

#include "wolf3d.h"

float normalize_angle_range(float angle)
{
    while (angle > PI)
        angle -= 2.0f * PI;
    while (angle < - PI)
        angle += 2.0f * PI;
    return angle;
}
