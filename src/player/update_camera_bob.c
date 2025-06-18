/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** update_camera_bob.c
*/

#include "wolf3d.h"

static float calculate_bob_speed(sfml_t *sfml)
{
    player_t *player = sfml->game->player;
    float momentum_magnitude = sqrtf(player->momentum_x * player->momentum_x +
        player->momentum_y * player->momentum_y);
    float speed_factor = momentum_magnitude / MAX_MOMENTUM;

    return BOB_SPEED * (0.6f + speed_factor * 0.4f);
}

static void update_bob_phase(sfml_t *sfml, float dt_factor)
{
    player_t *player = sfml->game->player;
    float bob_speed = calculate_bob_speed(sfml);

    player->bob_phase += bob_speed * dt_factor * 0.008f;
    if (player->bob_phase > PI * 2)
        player->bob_phase -= PI * 2;
}

static void calculate_height_bob(sfml_t *sfml)
{
    player_t *player = sfml->game->player;
    float max_amplitude = 10.0f;
    float momentum_magnitude = sqrtf(player->momentum_x * player->momentum_x +
        player->momentum_y * player->momentum_y);
    float speed_factor = momentum_magnitude / MAX_MOMENTUM;

    player->height_offset = sinf(player->bob_phase) *
        max_amplitude * speed_factor;
}

void calculate_weapon_bob(sfml_t *sfml)
{
    player_t *player = sfml->game->player;
    float momentum_magnitude = sqrtf(player->momentum_x * player->momentum_x +
        player->momentum_y * player->momentum_y);
    float speed_factor = momentum_magnitude / MAX_MOMENTUM;

    player->weapon_bob_x = sinf(player->bob_phase) * speed_factor * 10.0f;
}

static void unapply_momentum(sfml_t *sfml, player_t *player,
    float dt_factor)
{
    if (fabsf(player->height_offset) > 0.005f ||
        fabsf(player->weapon_bob_x) > 0.005f ||
        fabsf(player->weapon_bob_y) > 0.005f) {
        update_bob_phase(sfml, dt_factor * 0.5f);
        player->height_offset *= 0.9f;
        player->weapon_bob_x *= 0.9f;
        player->weapon_bob_y *= 0.9f;
    } else {
        player->height_offset = 0.0f;
        player->weapon_bob_x = 0.0f;
        player->weapon_bob_y = 0.0f;
    }
}

void update_camera_bob(sfml_t *sfml, float dt_factor)
{
    player_t *player = sfml->game->player;
    float momentum_magnitude = sqrtf(player->momentum_x * player->momentum_x +
        player->momentum_y * player->momentum_y);

    if (momentum_magnitude > 0.08f) {
        update_bob_phase(sfml, dt_factor);
        calculate_height_bob(sfml);
        calculate_weapon_bob(sfml);
    } else
        unapply_momentum(sfml, player, dt_factor);
}
