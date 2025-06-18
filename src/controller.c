/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** controller.c
*/

#include "wolf3d.h"

static void determine_controller_input(input_state_t *input, float joy_x,
    float joy_y, float right_trigger)
{
    if (right_trigger > CONTROLLER_DEADZONE)
        input->is_sprinting = 1.0f;
    if (fabs(joy_y) > CONTROLLER_DEADZONE) {
        if (joy_y < - CONTROLLER_DEADZONE)
            input->forward_key = 1;
        if (joy_y > CONTROLLER_DEADZONE)
            input->forward_key = -1;
    }
    if (fabs(joy_x) > CONTROLLER_DEADZONE) {
        if (joy_x < - CONTROLLER_DEADZONE)
            input->strafe_key = -1;
        if (joy_x > CONTROLLER_DEADZONE)
            input->strafe_key = 1;
    }
}

static void handle_controller_buttons(sfml_t *sfml)
{
    if (sfml->event.joystickButton.button == sfJoystickPovX) {
        render_mini_map(sfml);
        toggle_mini_map(sfml);
    }
    if (sfml->event.joystickButton.button == sfJoystickPovY) {
        if (sfml->game->game_substate == MINI_MAP)
            toggle_mini_map(sfml);
        else {
            play_sound(sfml, "menu_cancel", 100);
            change_bg_sprite(sfml);
            switch_state(sfml, (switch_state_args_t)
                {MENU, &update_menu, &events_menu});
            return;
        }
    }
}

static void process_weapon_change_joystick(sfml_t *sfml,
    int *weapon_switch_requested)
{
    int target_weapon = sfml->game->player->weapon->type;

    if (sfml->event.joystickButton.button == sfJoystickV)
        target_weapon = (target_weapon % 5) + 1;
    else if (sfml->event.joystickButton.button == sfJoystickU)
        target_weapon = ((target_weapon + 3) % 5) + 1;
    *weapon_switch_requested = target_weapon + 1;
}

void handle_controller_inputs(sfml_t *sfml,
    int *weapon_switch_requested)
{
    static int stop_firing_requested = 0;
    float right_trigger =
        sfJoystick_getAxisPosition(CONTROLLER_ID, sfJoystickR);

    if (right_trigger > 0)
        handle_shooting(sfml);
    if (right_trigger < 0 && !sfMouse_isButtonPressed(sfMouseLeft))
        handle_release_shooting(sfml, &stop_firing_requested);
    if (sfml->event.type == sfEvtJoystickButtonPressed) {
        process_weapon_change_joystick(sfml, weapon_switch_requested);
        handle_controller_buttons(sfml);
    }
    if (sfml->game->game_substate == MINI_MAP)
        mini_map_zoom_controller(sfml);
    handle_stop_firing_requested(sfml, &stop_firing_requested);
}

void get_controller_input(input_state_t *input)
{
    float joy_x;
    float joy_y;
    float right_trigger;

    if (!sfJoystick_isConnected(CONTROLLER_ID))
        return;
    joy_x = sfJoystick_getAxisPosition(CONTROLLER_ID, sfJoystickX);
    joy_y = sfJoystick_getAxisPosition(CONTROLLER_ID, sfJoystickY);
    right_trigger = sfJoystick_getAxisPosition(CONTROLLER_ID, sfJoystickZ);
    determine_controller_input(input, joy_x, joy_y, right_trigger);
}
