/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** flashlight.c
*/

#include "wolf3d.h"

void toggle_flashlight(sfml_t *sfml)
{
    if (!sfml->game->player)
        return;
    sfml->game->player->flashlight_active =
        !sfml->game->player->flashlight_active;
    play_sound(sfml, "switch", 30);
}

static float get_brightness(player_t *player, float world_x,
    float world_y, float brightness)
{
    float dx = world_x - (player->x + cos(player->angle) *
        LIGHT_CENTER_DISTANCE);
    float dy = world_y - (player->y + sin(player->angle) *
        LIGHT_CENTER_DISTANCE);
    float distance = sqrtf(dx * dx + dy * dy);
    float final_brightness = brightness;

    if (player->flashlight_active) {
        if (distance <= LIGHT_RADIUS) {
            final_brightness = (distance < LIGHT_RADIUS * 0.7f) ? brightness *
                1.0f : brightness * (1.0f - (((distance - LIGHT_RADIUS * 0.7f)
                / (LIGHT_RADIUS * 0.3f)) * 0.7f));
        } else
            final_brightness = brightness * 0.3f;
    } else
        final_brightness = brightness * 0.5f;
    return final_brightness;
}

float apply_flashlight(sfml_t *sfml, float world_x,
    float world_y, float brightness)
{
    player_t *player = sfml->game->player;
    float final_brightness = get_brightness(player, world_x,
        world_y, brightness);
    float flash_intens;
    float flash_dx = world_x - player->x;
    float flash_dy = world_y - player->y;
    float flash_distance = sqrtf(flash_dx * flash_dx + flash_dy * flash_dy);
    float angle = fabs(normalize_angle_range(atan2f(flash_dy, flash_dx) -
        player->angle));

    if (player->muzzle_flash_timer > 0.0f) {
        flash_intens = (player->muzzle_flash_timer / MUZZLE_FLASH_DURATION)
        * MUZZLE_FLASH_INTENSITY;
        if (flash_distance > 0.1f && angle <= FLASH_CONE)
            final_brightness = fminf(1.0f, final_brightness + (flash_intens *
            (1.0f / (1.0f + flash_distance * 0.005f)) *
            (1.0f - (angle / FLASH_CONE))));
    }
    return final_brightness;
}
