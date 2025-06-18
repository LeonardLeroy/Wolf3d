/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** events_menu.c
*/

#include "wolf3d.h"

static void start_game(sfml_t *sfml)
{
    if (!sfml->menu->game_started)
        sfml->menu->game_started = 1;
    else
        reset_game(sfml);
    handle_transition_state(sfml);
    switch_state(sfml, (switch_state_args_t)
        {GAME, &update_game, &game_events});
}

static void select_to_menu(sfml_t *sfml, int cur_select)
{
    play_sound(sfml, "pistol", 100);
    switch (cur_select) {
        case 0:
            start_game(sfml);
            break;
        case 1:
            switch_menu_substate(sfml, (switch_menu_substate_args_t)
                {OPTIONS, &update_options, &events_options});
            break;
        case 2:
            sfRenderWindow_close(sfml->window);
            break;
    }
}

static void position_skull_selector(sfml_t *sfml, int selection)
{
    sfVector2f positions[] = {
        {sfSprite_getPosition(sfml->menu->start_b->sprite).x - 100,
            sfSprite_getPosition(sfml->menu->start_b->sprite).y},
        {sfSprite_getPosition(sfml->menu->options_b->sprite).x - 100,
            sfSprite_getPosition(sfml->menu->options_b->sprite).y},
        {sfSprite_getPosition(sfml->menu->exit_b->sprite).x - 100,
            sfSprite_getPosition(sfml->menu->exit_b->sprite).y}
    };

    sfSprite_setPosition(sfml->menu->skull_sheet->sprite,
        positions[selection]);
}

static int get_skull_selection(sfml_t *sfml)
{
    sfVector2f positions[] = {
        {sfSprite_getPosition(sfml->menu->start_b->sprite).x - 100,
            sfSprite_getPosition(sfml->menu->start_b->sprite).y},
        {sfSprite_getPosition(sfml->menu->options_b->sprite).x - 100,
            sfSprite_getPosition(sfml->menu->options_b->sprite).y},
        {sfSprite_getPosition(sfml->menu->exit_b->sprite).x - 100,
            sfSprite_getPosition(sfml->menu->exit_b->sprite).y}
    };

    for (int i = 0; i < 3; i++) {
        if (positions[i].x == sfSprite_getPosition(
            sfml->menu->skull_sheet->sprite).x &&
            positions[i].y == sfSprite_getPosition(
            sfml->menu->skull_sheet->sprite).y)
            return i;
    }
    return 0;
}

static void handle_key_press(sfml_t *sfml, sfKeyCode key)
{
    int current_selection = get_skull_selection(sfml);

    if (key == sfKeyUp || key == sfKeyDown)
        play_sound(sfml, "menu_select", 100);
    if (key == sfKeyUp)
        current_selection = (current_selection - 1 + 3) % 3;
    if (key == sfKeyDown)
        current_selection = (current_selection + 1) % 3;
    if (key == sfKeyEnter || key == sfKeySpace)
        select_to_menu(sfml, current_selection);
    if (key == sfKeyEscape) {
        if (sfml->menu->game_started)
            switch_state(sfml, (switch_state_args_t)
                {GAME, &update_game, &game_events});
        else
            sfml->menu->intro = 1;
    }
    position_skull_selector(sfml, current_selection);
}

void handle_keys_input(sfml_t *sfml)
{
    static int was_pressed = 0;

    if ((sfKeyboard_isKeyPressed(sfKeyUp) || sfKeyboard_isKeyPressed(sfKeyDown)
        || sfKeyboard_isKeyPressed(sfKeyEnter) || sfKeyboard_isKeyPressed(
        sfKeySpace) || sfKeyboard_isKeyPressed(sfKeyEscape)) && !was_pressed) {
        if (sfml->menu->intro) {
            sfml->menu->intro = 0;
            play_sound(sfml, "menu_cancel", 100);
            return;
        }
        handle_key_press(sfml, sfml->event.key.code);
        was_pressed = 1;
    }
    if (sfml->event.type == sfEvtKeyReleased && was_pressed)
        was_pressed = 0;
}

static void handle_other_mouse_input(sfml_t *sfml, sfVector2i m_pos)
{
    if (sfFloatRect_contains(&sfml->menu->options_b->bounds,
        m_pos.x, m_pos.y)) {
        position_skull_selector(sfml, 1);
        switch_menu_substate(sfml, (switch_menu_substate_args_t)
            {OPTIONS, &update_options, &events_options});
        play_sound(sfml, "pistol", 100);
    }
    if (sfFloatRect_contains(&sfml->menu->exit_b->bounds, m_pos.x, m_pos.y)) {
        position_skull_selector(sfml, 2);
        sfRenderWindow_close(sfml->window);
    }
    if (sfFloatRect_contains(&sfml->menu->back_b->bounds, m_pos.x, m_pos.y)) {
        if (sfml->menu->game_started)
            switch_state(sfml, (switch_state_args_t)
                {GAME, &update_game, &game_events});
        else
            sfml->menu->intro = 1;
        play_sound(sfml, "menu_cancel", 100);
    }
}

void handle_mouse_input(sfml_t *sfml, sfVector2i m_pos)
{
    if (sfml->menu->intro) {
        sfml->menu->intro = 0;
        play_sound(sfml, "menu_cancel", 100);
        return;
    }
    if (sfFloatRect_contains(&sfml->menu->start_b->bounds, m_pos.x, m_pos.y)) {
        if (!sfml->menu->game_started) {
            play_sound(sfml, "pistol", 100);
            sfml->menu->game_started = 1;
        } else
            reset_game(sfml);
        position_skull_selector(sfml, 0);
        handle_transition_state(sfml);
        switch_state(sfml, (switch_state_args_t)
            {GAME, &update_game, &game_events});
    }
    handle_other_mouse_input(sfml, m_pos);
}

void events_menu(sfml_t *sfml)
{
    sfVector2i m_pos = sfMouse_getPositionRenderWindow(sfml->window);

    handle_keys_input(sfml);
    if (sfml->event.type == sfEvtMouseButtonPressed &&
        sfml->event.mouseButton.button == sfMouseLeft) {
        handle_mouse_input(sfml, m_pos);
    }
}
