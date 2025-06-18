/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** free_options.c
*/

#include "wolf3d.h"

static void free_menu_button(menu_button_t *button)
{
    if (!button)
        return;
    if (button->texture) {
        sfTexture_destroy(button->texture);
        button->texture = NULL;
    }
    if (button->sprite) {
        sfSprite_destroy(button->sprite);
        button->sprite = NULL;
    }
    free(button);
}

static void free_volume_controls(menu_button_t **volume_text)
{
    for (int i = 0; i <= 10; i++) {
        if (volume_text[i]) {
            free_menu_button(volume_text[i]);
            volume_text[i] = NULL;
        }
    }
}

static void free_volume_and_framerate_buttons(options_t *opt)
{
    free_menu_button(opt->sfx_label);
    free_menu_button(opt->sfx_minus);
    free_menu_button(opt->sfx_plus);
    free_menu_button(opt->music_label);
    free_menu_button(opt->music_minus);
    free_menu_button(opt->music_plus);
    free_menu_button(opt->framerate_label);
    free_menu_button(opt->framerate_minus);
    free_menu_button(opt->framerate_plus);
}

void free_options(sfml_t *sfml)
{
    options_t *opt = sfml->menu->options;

    if (!opt || !opt->exit)
        return;
    free_menu_button(opt->exit);
    free_menu_button(opt->fullscreen_label);
    free_menu_button(opt->fullscreen_yes);
    free_menu_button(opt->fullscreen_no);
    free_volume_and_framerate_buttons(opt);
    free_menu_button(opt->load_button);
    free_volume_controls(opt->sfx_volume_text);
    free_volume_controls(opt->music_volume_text);
    for (int i = 0; i < 10; i++) {
        if (opt->framerate_text[i]) {
            free_menu_button(opt->framerate_text[i]);
            opt->framerate_text[i] = NULL;
        }
    }
    free(opt);
    sfml->menu->options = NULL;
}
