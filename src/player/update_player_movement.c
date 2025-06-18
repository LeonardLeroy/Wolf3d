/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** update_player_movement.c
*/

#include "wolf3d.h"

static void apply_doom_strafe(sfml_t *sfml, float dt_factor,
    int forward_key, int strafe_key)
{
    player_t *player = sfml->game->player;
    float strafe_thrust = (forward_key > 0 && strafe_key != 0 && (
        (sfMouse_getPositionRenderWindow(sfml->window).x
        != (int)(sfRenderWindow_getSize(sfml->window).x / 2)) ||
        sfKeyboard_isKeyPressed(sfKeyLeft) ||
        sfKeyboard_isKeyPressed(sfKeyRight))) ? 50.0f : STRAFE_THRUST;
    float accel_factor = ACCELERATION * dt_factor;

    if (forward_key != 0) {
        player->momentum_x += cos(player->angle) * FORWARD_THRUST
            * accel_factor * forward_key;
        player->momentum_y += sin(player->angle) * FORWARD_THRUST
            * accel_factor * forward_key;
    }
    if (strafe_key != 0) {
        player->momentum_x += cos(player->angle + PI / 2) * strafe_thrust
            * accel_factor * strafe_key;
        player->momentum_y += sin(player->angle + PI / 2) * strafe_thrust
            * accel_factor * strafe_key;
    }
}

static float calculate_max_momentum(sfml_t *sfml, int forward_key,
    int strafe_key, float is_sprinting)
{
    float max_momentum = MAX_MOMENTUM;
    int is_turning = (sfMouse_getPositionRenderWindow(sfml->window).x
        != (int)(sfRenderWindow_getSize(sfml->window).x / 2)) ||
        sfKeyboard_isKeyPressed(sfKeyLeft) ||
        sfKeyboard_isKeyPressed(sfKeyRight);

    if (forward_key != 0 && strafe_key != 0)
        max_momentum *= 1.28f;
    if (forward_key > 0 && strafe_key != 0 && is_turning)
        max_momentum = MAX_MOMENTUM * 1.41f;
    if (is_sprinting)
        max_momentum *= 1.4f;
    return max_momentum;
}

void get_keyboard_input(input_state_t *input)
{
    input->forward_key = 0;
    input->strafe_key = 0;
    input->is_sprinting = 0.0f;
    if (sfKeyboard_isKeyPressed(sfKeyLShift) ||
        sfKeyboard_isKeyPressed(sfKeyRShift))
        input->is_sprinting = 1.0f;
    if (sfKeyboard_isKeyPressed(sfKeyUp) || sfKeyboard_isKeyPressed(sfKeyZ))
        input->forward_key = 1;
    if (sfKeyboard_isKeyPressed(sfKeyDown) || sfKeyboard_isKeyPressed(sfKeyS))
        input->forward_key = -1;
    if (sfKeyboard_isKeyPressed(sfKeyQ))
        input->strafe_key = -1;
    if (sfKeyboard_isKeyPressed(sfKeyD))
        input->strafe_key = 1;
}

static void limit_player_momentum_to_max(sfml_t *sfml, float max_momentum)
{
    player_t *player = sfml->game->player;
    float momentum_magnitude;
    float scale;

    momentum_magnitude = sqrtf(player->momentum_x * player->momentum_x +
        player->momentum_y * player->momentum_y);
    if (momentum_magnitude > max_momentum) {
        scale = max_momentum / momentum_magnitude;
        player->momentum_x *= scale;
        player->momentum_y *= scale;
    }
}

static void combine_input_states(input_state_t *keyboard,
    input_state_t *controller, input_state_t *final)
{
    final->forward_key = controller->forward_key != 0 ?
        controller->forward_key : keyboard->forward_key;
    final->strafe_key = controller->strafe_key != 0 ?
        controller->strafe_key : keyboard->strafe_key;
    final->is_sprinting = (keyboard->is_sprinting > 0.0f ||
        controller->is_sprinting > 0.0f) ? 1.0f : 0.0f;
}

void update_player_movement(sfml_t *sfml, float dt_factor)
{
    input_state_t keyboard_input = {0};
    input_state_t controller_input = {0};
    input_state_t final_input = {0};

    get_keyboard_input(&keyboard_input);
    get_controller_input(&controller_input);
    combine_input_states(&keyboard_input, &controller_input,
        &final_input);
    apply_doom_strafe(sfml, dt_factor, final_input.forward_key,
        final_input.strafe_key);
    limit_player_momentum_to_max(sfml, calculate_max_momentum(sfml,
        final_input.forward_key,
        final_input.strafe_key,
        final_input.is_sprinting));
}
