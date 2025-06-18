/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** events_game.c
*/

#include "wolf3d.h"

void handle_stop_firing_requested(sfml_t *sfml,
    int *stop_firing_requested)
{
    if (*stop_firing_requested == 1 &&
        sfml->game->player->weapon->sheet->current_frame ==
            sfml->game->player->weapon->sheet->frames - 1) {
        sfml->game->player->weapon->shooting = 0;
        *stop_firing_requested = 0;
    }
}

int will_collide_with_wall(sfml_t *sfml, float new_x, float new_y)
{
    float padding = 20.0f;
    int map_x;
    int map_y;

    if (new_x < padding || new_x >= MAP_WIDTH * TILE_SIZE - padding ||
        new_y < padding || new_y >= MAP_HEIGHT * TILE_SIZE - padding) {
        return 1;
    }
    map_x = (int)(new_x / TILE_SIZE);
    map_y = (int)(new_y / TILE_SIZE);
    if (sfml->game->map[map_y][map_x] != 0)
        return 1;
    return 0;
}

static void handle_numbers_input(sfKeyCode key,
    int *weapon_switch_requested)
{
    if (key == sfKeyNum1)
        *weapon_switch_requested = 1;
    if (key == sfKeyNum2)
        *weapon_switch_requested = 2;
    if (key == sfKeyNum3)
        *weapon_switch_requested = 3;
    if (key == sfKeyQuote || key == sfKeyNum4)
        *weapon_switch_requested = 4;
    if (key == sfKeyNum5)
        *weapon_switch_requested = 5;
}

static void handle_keys(sfml_t *sfml)
{
    if (sfml->event.key.code == sfKeyR) {
        free_enemies(sfml);
        generate_procedural_map(sfml);
        init_enemies(sfml);
        if (sfml->game->ai_manager) {
            cleanup_enemy_pathfinding(sfml->game->ai_manager);
            sfml->game->ai_manager = init_enemy_pathfinding();
        }
    }
    if (sfml->event.key.code == sfKeyTab) {
        render_mini_map(sfml);
        toggle_mini_map(sfml);
    }
    if (sfml->event.key.code == sfKeyF)
        toggle_fullscreen(sfml);
    if (sfml->event.key.code == sfKeyL)
        toggle_flashlight(sfml);
}

static void game_key_events(sfml_t *sfml, int *weapon_switch_requested)
{
    if (sfml->event.key.code == sfKeyEscape) {
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
    handle_keys(sfml);
    handle_numbers_input(sfml->event.key.code, weapon_switch_requested);
}

static void process_weapon_change(sfml_t *sfml, int *weapon_switch_requested)
{
    int target_weapon = sfml->game->player->weapon->type;

    if (sfml->event.mouseWheelScroll.delta > 0)
        target_weapon = (target_weapon % 5) + 1;
    else if (sfml->event.mouseWheelScroll.delta < 0)
        target_weapon = ((target_weapon + 3) % 5) + 1;
    *weapon_switch_requested = target_weapon + 1;
}

void handle_key_inputs(sfml_t *sfml, int *weapon_switch_requested)
{
    static int stop_firing_requested = 0;

    if (sfKeyboard_isKeyPressed(sfKeyLControl) ||
        sfKeyboard_isKeyPressed(sfKeyRControl)) {
        handle_shooting(sfml);
    }
    if (sfml->event.type == sfEvtKeyPressed)
        game_key_events(sfml, weapon_switch_requested);
    if (sfml->event.type == sfEvtKeyReleased &&
        (sfml->event.key.code == sfKeyLControl ||
        sfml->event.key.code == sfKeyRControl))
        handle_release_shooting(sfml, &stop_firing_requested);
    handle_stop_firing_requested(sfml, &stop_firing_requested);
}

void handle_mouse_inputs(sfml_t *sfml, int *weapon_switch_requested)
{
    static int stop_firing_requested = 0;

    if (sfMouse_isButtonPressed(sfMouseLeft))
        handle_shooting(sfml);
    else if (sfml->event.type == sfEvtMouseButtonReleased &&
        sfml->event.mouseButton.button == sfMouseLeft)
        handle_release_shooting(sfml, &stop_firing_requested);
    if (sfml->event.type == sfEvtMouseWheelScrolled) {
        process_weapon_change(sfml, weapon_switch_requested);
        mini_map_zoom(sfml);
    }
    handle_stop_firing_requested(sfml, &stop_firing_requested);
}

void game_events(sfml_t *sfml)
{
    static int weapon_switch_requested = 0;

    handle_key_inputs(sfml, &weapon_switch_requested);
    handle_mouse_inputs(sfml, &weapon_switch_requested);
    if (sfJoystick_isConnected(CONTROLLER_ID))
        handle_controller_inputs(sfml, &weapon_switch_requested);
    if (weapon_switch_requested != 0 &&
        (!sfml->game->player->weapon->shooting ||
        (sfml->game->player->weapon->type == CHAINGUN ||
        sfml->game->player->weapon->type == FIST))) {
        switch_weapon(sfml, (int)weapon_switch_requested - 1);
        weapon_switch_requested = 0;
    }
}
