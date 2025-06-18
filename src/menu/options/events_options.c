/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** events_options.c
*/

#include "wolf3d.h"

static void handle_fullscreen_toggle(sfml_t *sfml, sfVector2i m_pos)
{
    options_t *opt = sfml->menu->options;

    if (sfFloatRect_contains(&opt->fullscreen_yes->bounds,
        m_pos.x, m_pos.y) && !opt->is_fullscreen) {
        play_sound(sfml, "menu_select", 100);
        toggle_fullscreen(sfml);
    } else if (sfFloatRect_contains(&opt->fullscreen_no->bounds,
        m_pos.x, m_pos.y) && opt->is_fullscreen) {
        play_sound(sfml, "menu_select", 100);
        toggle_fullscreen(sfml);
    }
}

static void decrease_music_volume(sfml_t *sfml)
{
    options_t *opt = sfml->menu->options;

    play_sound(sfml, "menu_select", 100);
    if (opt->music_volume > 0) {
        opt->music_volume--;
        set_music_volume(sfml, opt->music_volume * 10);
        position_plus_button(opt->music_volume_text[opt->music_volume],
            opt->music_plus);
    }
}

static void increase_music_volume(sfml_t *sfml)
{
    options_t *opt = sfml->menu->options;

    play_sound(sfml, "menu_select", 100);
    if (opt->music_volume < 10) {
        opt->music_volume++;
        set_music_volume(sfml, opt->music_volume * 10);
        position_plus_button(opt->music_volume_text[opt->music_volume],
            opt->music_plus);
    }
}

static void decrease_sfx_volume(sfml_t *sfml)
{
    options_t *opt = sfml->menu->options;

    play_sound(sfml, "menu_select", 100);
    if (opt->sfx_volume > 0) {
        opt->sfx_volume--;
        set_sfx_volume(sfml, opt->sfx_volume * 10);
        position_plus_button(opt->sfx_volume_text[opt->sfx_volume],
            opt->sfx_plus);
    }
}

static void increase_sfx_volume(sfml_t *sfml)
{
    options_t *opt = sfml->menu->options;

    play_sound(sfml, "menu_select", 100);
    if (opt->sfx_volume < 10) {
        opt->sfx_volume++;
        set_sfx_volume(sfml, opt->sfx_volume * 10);
        position_plus_button(opt->sfx_volume_text[opt->sfx_volume],
            opt->sfx_plus);
    }
}

static void handle_volume(sfml_t *sfml, sfVector2i m_pos)
{
    options_t *opt = sfml->menu->options;

    if (sfFloatRect_contains(&opt->sfx_minus->bounds, m_pos.x, m_pos.y)) {
        decrease_sfx_volume(sfml);
        return;
    }
    if (sfFloatRect_contains(&opt->sfx_plus->bounds, m_pos.x, m_pos.y))
        increase_sfx_volume(sfml);
    if (sfFloatRect_contains(&opt->music_minus->bounds, m_pos.x, m_pos.y)) {
        decrease_music_volume(sfml);
        return;
    }
    if (sfFloatRect_contains(&opt->music_plus->bounds, m_pos.x, m_pos.y))
        increase_music_volume(sfml);
}

static void decrease_framerate(sfml_t *sfml)
{
    options_t *opt = sfml->menu->options;
    int framerate_values[] = {30, 60, 75, 90, 120, 144, 165, 180, 200, 240};

    play_sound(sfml, "menu_select", 100);
    if (opt->framerate_index > 0) {
        opt->framerate_index--;
        if (sfml->window) {
            sfRenderWindow_setVerticalSyncEnabled(sfml->window, 0);
            sfRenderWindow_setFramerateLimit(sfml->window,
                framerate_values[opt->framerate_index]);
        }
        position_plus_button(opt->framerate_text[opt->framerate_index],
            opt->framerate_plus);
    }
}

static void increase_framerate(sfml_t *sfml)
{
    options_t *opt = sfml->menu->options;
    int framerate_values[] = {30, 60, 75, 90, 120, 144, 165, 180, 200, 240};

    play_sound(sfml, "menu_select", 100);
    if (opt->framerate_index < 9) {
        opt->framerate_index++;
        if (sfml->window) {
            sfRenderWindow_setVerticalSyncEnabled(sfml->window, 0);
            sfRenderWindow_setFramerateLimit(sfml->window,
            framerate_values[opt->framerate_index]);
        }
        position_plus_button(opt->framerate_text[opt->framerate_index],
            opt->framerate_plus);
    }
}

static void handle_buttons(sfml_t *sfml, sfVector2i m_pos)
{
    handle_fullscreen_toggle(sfml, m_pos);
    handle_volume(sfml, m_pos);
    if (sfFloatRect_contains(&sfml->menu->options->framerate_minus->bounds,
        m_pos.x, m_pos.y)) {
        decrease_framerate(sfml);
        return;
    }
    if (sfFloatRect_contains(&sfml->menu->options->framerate_plus->bounds,
        m_pos.x, m_pos.y))
        increase_framerate(sfml);
    if (sfFloatRect_contains(&sfml->menu->options->load_button->bounds,
        m_pos.x, m_pos.y)) {
        play_sound(sfml, "menu_select", 100);
        switch_menu_substate(sfml, (switch_menu_substate_args_t)
            {SAVES, &update_saves, &events_saves});
    }
}

void events_options(sfml_t *sfml)
{
    sfVector2i m_pos = sfMouse_getPositionRenderWindow(sfml->window);

    if (sfml->event.type == sfEvtMouseButtonPressed &&
        sfMouse_isButtonPressed(sfMouseLeft)) {
        if (sfFloatRect_contains(&sfml->menu->options->exit->bounds,
            m_pos.x, m_pos.y)) {
            play_sound(sfml, "menu_cancel", 100);
            switch_menu_substate(sfml, (switch_menu_substate_args_t)
                {MAIN, &update_menu, &events_menu});
        }
        handle_buttons(sfml, m_pos);
    }
    if (sfml->event.type == sfEvtKeyPressed &&
        sfKeyboard_isKeyPressed(sfKeyEscape)) {
        play_sound(sfml, "menu_cancel", 100);
        switch_menu_substate(sfml, (switch_menu_substate_args_t)
            {MAIN, &update_menu, &events_menu});
    }
}
