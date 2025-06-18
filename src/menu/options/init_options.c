/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** init_options.c
*/

#include "wolf3d.h"

static void init_fullscreen_options(sfml_t *sfml, float y_position,
    float left_margin, float right_margin)
{
    options_t *opt = sfml->menu->options;
    sfVector2u window_size = sfRenderWindow_getSize(sfml->window);

    opt->fullscreen_label = create_button_with_scale("options/o_fullscreen",
        4.75);
    opt->fullscreen_yes = create_button_with_scale("options/o_yes", 1.2);
    opt->fullscreen_no = create_button_with_scale("options/o_no", 1.2);
    sfSprite_setPosition(opt->fullscreen_label->sprite,
        (sfVector2f){left_margin, y_position});
    sfSprite_setPosition(opt->fullscreen_yes->sprite,
        (sfVector2f){window_size.x - right_margin, y_position});
    sfSprite_setPosition(opt->fullscreen_no->sprite,
        (sfVector2f){window_size.x - right_margin, y_position});
    opt->fullscreen_label->bounds =
    sfSprite_getGlobalBounds(opt->fullscreen_label->sprite);
    opt->fullscreen_yes->bounds =
    sfSprite_getGlobalBounds(opt->fullscreen_yes->sprite);
    opt->fullscreen_no->bounds =
    sfSprite_getGlobalBounds(opt->fullscreen_no->sprite);
    opt->is_fullscreen = 0;
}

static void init_load_button(sfml_t *sfml)
{
    sfml->menu->options->load_button = create_button_with_scale(
        "options/o_load", 4.75);
    sfSprite_setPosition(sfml->menu->options->load_button->sprite,
        (sfVector2f){LEFT_MARGIN, START_Y + SPACING * 4});
    sfml->menu->options->load_button->bounds = sfSprite_getGlobalBounds(
        sfml->menu->options->load_button->sprite);
}

static void init_exit_and_finalize(sfml_t *sfml)
{
    sfVector2u window_size;
    float centered_x;

    sfml->menu->options->exit = create_button_with_scale("options/o_exit",
        4.75);
    window_size = sfRenderWindow_getSize(sfml->window);
    centered_x = (window_size.x - sfSprite_getGlobalBounds(
        sfml->menu->options->exit->sprite).width) / 2.0f;
    sfSprite_setPosition(sfml->menu->options->exit->sprite,
        (sfVector2f){centered_x, START_Y + SPACING * 5});
    sfml->menu->options->exit->bounds = sfSprite_getGlobalBounds(
        sfml->menu->options->exit->sprite);
    set_music_volume(sfml, sfml->menu->options->music_volume * 10);
    set_sfx_volume(sfml, sfml->menu->options->sfx_volume * 10);
}

static void create_framerate_buttons(sfml_t *sfml, float scale)
{
    const char *framerate_names[] = {
        "options/thirty", "options/sixty", "options/seventy_five",
        "options/ninety", "options/one_twenty", "options/one_fortyfour",
        "options/one_sixtyfive", "options/one_eighty", "options/two_hundred",
        "options/two_forty"
    };

    sfml->menu->options->framerate_label = create_button_with_scale(
        "options/o_framerate", 4.75 * scale);
    sfml->menu->options->framerate_minus = create_button_with_scale(
        "options/o_minus", 1.2 * scale);
    sfml->menu->options->framerate_plus = create_button_with_scale(
        "options/o_plus", 1.2 * scale);
    for (int i = 0; i < 10; i++)
        sfml->menu->options->framerate_text[i] =
        create_button_with_scale(framerate_names[i], 1.2 * scale);
}

static void calculate_framerate_positions(sfml_t *sfml, float *y_position,
    float *minus_x, float *consistent_spacing)
{
    float scale = get_scale_factor(sfml);
    sfVector2u window_size = sfRenderWindow_getSize(sfml->window);

    *y_position = (START_Y + SPACING * 3) * sfml->window_size->scale_factor_y;
    *minus_x = window_size.x - RIGHT_MARGIN * sfml->window_size->scale_factor_x
    - 100 * scale;
    *consistent_spacing = 30 * scale;
}

static void position_framerate_label_and_minus(sfml_t *sfml, float minus_x,
    float y_position)
{
    if (sfml->menu->options->framerate_label) {
        sfSprite_setPosition(sfml->menu->options->framerate_label->sprite,
            (sfVector2f){LEFT_MARGIN * sfml->window_size->scale_factor_x,
                y_position});
        sfml->menu->options->framerate_label->bounds =
        sfSprite_getGlobalBounds(sfml->menu->options->framerate_label->sprite);
    }
    if (sfml->menu->options->framerate_minus) {
        sfSprite_setPosition(sfml->menu->options->framerate_minus->sprite,
            (sfVector2f){minus_x, y_position});
        sfml->menu->options->framerate_minus->bounds =
        sfSprite_getGlobalBounds(sfml->menu->options->framerate_minus->sprite);
    }
}

static void position_framerate_texts(sfml_t *sfml, float minus_x,
    float y_position, float consistent_spacing)
{
    float percent_x = minus_x + (sfml->menu->options->framerate_minus ?
        sfSprite_getGlobalBounds(sfml->menu->options->framerate_minus->sprite).
        width : 0) + consistent_spacing;

    for (int i = 0; i < 10; i++) {
        if (sfml->menu->options->framerate_text[i]) {
            sfSprite_setPosition(sfml->menu->options->framerate_text[i]->
            sprite, (sfVector2f){percent_x, y_position});
            sfml->menu->options->framerate_text[i]->bounds =
            sfSprite_getGlobalBounds(
            sfml->menu->options->framerate_text[i]->sprite);
        }
    }
}

static void setup_framerate_plus_button(sfml_t *sfml)
{
    sfml->menu->options->framerate_index = 1;
    if (sfml->menu->options->framerate_text[
        sfml->menu->options->framerate_index])
        position_plus_button(sfml->menu->options->framerate_text[
            sfml->menu->options->framerate_index],
            sfml->menu->options->framerate_plus);
    if (sfml->menu->options->framerate_plus) {
        sfml->menu->options->framerate_plus->bounds =
        sfSprite_getGlobalBounds(sfml->menu->options->framerate_plus->sprite);
    }
}

static void init_framerate_options(sfml_t *sfml)
{
    float scale = get_scale_factor(sfml);
    float y_position;
    float minus_x;
    float consistent_spacing;

    calculate_framerate_positions(sfml, &y_position, &minus_x,
        &consistent_spacing);
    create_framerate_buttons(sfml, scale);
    position_framerate_label_and_minus(sfml, minus_x, y_position);
    position_framerate_texts(sfml, minus_x, y_position, consistent_spacing);
    setup_framerate_plus_button(sfml);
}

void init_options(sfml_t *sfml)
{
    sfml->menu->options = salloc(sizeof(options_t));
    init_fullscreen_options(sfml, START_Y, LEFT_MARGIN, RIGHT_MARGIN);
    init_volume_options(sfml);
    init_framerate_options(sfml);
    init_load_button(sfml);
    init_exit_and_finalize(sfml);
}
