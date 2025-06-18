/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** events_win_lose.c
*/

#include "wolf3d.h"

static void handle_restart_game(sfml_t *sfml)
{
    play_sound(sfml, "menu_select", 100);
    free_win_lose(sfml);
    reset_game(sfml);
    switch_state(sfml, (switch_state_args_t){GAME, &update_game,
        &game_events});
}

static void handle_return_to_main_menu(sfml_t *sfml)
{
    play_sound(sfml, "menu_cancel", 100);
    free_win_lose(sfml);
    change_bg_sprite(sfml);
    switch_state(sfml, (switch_state_args_t){MENU, &update_menu,
        &events_menu});
}

static void handle_exit_game(sfml_t *sfml)
{
    play_sound(sfml, "menu_cancel", 100);
    sfRenderWindow_close(sfml->window);
}

static void handle_code(sfml_t *sfml)
{
    switch (sfml->event.key.code) {
        case sfKeyEnter:
        case sfKeySpace:
        case sfKeyR:
            handle_restart_game(sfml);
            break;
        case sfKeyEscape:
        case sfKeyM:
            handle_return_to_main_menu(sfml);
            break;
        case sfKeyQ:
            handle_exit_game(sfml);
            break;
        default:
            break;
    }
}

static void handle_keyboard_input(sfml_t *sfml)
{
    static int key_pressed = 0;

    if (!sfml->win_lose)
        return;
    if (sfml->win_lose->transition_phase != 2)
        return;
    if (sfml->event.type == sfEvtKeyPressed && !key_pressed) {
        key_pressed = 1;
        handle_code(sfml);
    }
    if (sfml->event.type == sfEvtKeyReleased)
        key_pressed = 0;
}

static bool is_valid_mouse_click(sfml_t *sfml, sfVector2i *mouse_pos)
{
    if (!sfml->win_lose)
        return false;
    if (sfml->event.type != sfEvtMouseButtonPressed ||
        sfml->event.mouseButton.button != sfMouseLeft) {
        return false;
    }
    if (sfml->win_lose->transition_phase != 2)
        return false;
    *mouse_pos = sfMouse_getPositionRenderWindow(sfml->window);
    return true;
}

static void handle_mouse_input(sfml_t *sfml)
{
    sfVector2i mouse_pos;

    if (!is_valid_mouse_click(sfml, &mouse_pos))
        return;
    if (sfFloatRect_contains(&sfml->win_lose->restart_button->bounds,
        mouse_pos.x, mouse_pos.y)) {
        handle_restart_game(sfml);
        return;
    }
    if (sfFloatRect_contains(&sfml->win_lose->main_menu_button->bounds,
        mouse_pos.x, mouse_pos.y)) {
        handle_return_to_main_menu(sfml);
        return;
    }
    if (sfFloatRect_contains(&sfml->win_lose->exit_button->bounds,
        mouse_pos.x, mouse_pos.y)) {
        handle_exit_game(sfml);
        return;
    }
}

static void skip_transition_on_input(sfml_t *sfml)
{
    int skip = 0;

    if (!sfml->win_lose)
        return;
    if (sfml->win_lose->transition_phase < 2) {
        if (sfml->event.type == sfEvtKeyPressed ||
            sfml->event.type == sfEvtMouseButtonPressed) {
            skip = 1;
        }
        if (skip) {
            sfml->win_lose->transition_phase = 2;
            sfml->win_lose->fade_timer = 1.0f;
            sfRectangleShape_setFillColor(sfml->win_lose->fade_overlay,
                sfColor_fromRGBA(0, 0, 0, 200));
        }
    }
}

void events_win_lose(sfml_t *sfml)
{
    skip_transition_on_input(sfml);
    handle_mouse_input(sfml);
    handle_keyboard_input(sfml);
}
