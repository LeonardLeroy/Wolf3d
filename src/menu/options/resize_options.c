/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-evan.lafolie
** File description:
** resize_options.c
*/

#include "wolf3d.h"

void config_menu_button(menu_button_t *button, float scale, float pos_x,
    float pos_y)
{
    if (!button)
        return;
    sfSprite_setScale(button->sprite, (sfVector2f){scale, scale});
    sfSprite_setPosition(button->sprite, (sfVector2f){pos_x, pos_y});
    button->bounds = sfSprite_getGlobalBounds(button->sprite);
}

static void update_fullscreen_options(const menu_layout_params_t *params)
{
    if (params->opt->fullscreen_label)
        config_menu_button(params->opt->fullscreen_label, params->scale *
            4.75f, params->left_margin, params->start_y);
    if (params->opt->fullscreen_yes)
        config_menu_button(params->opt->fullscreen_yes, params->scale * 1.2f,
            params->minus_x, params->start_y);
    if (params->opt->fullscreen_no)
        config_menu_button(params->opt->fullscreen_no, params->scale * 1.2f,
            params->minus_x, params->start_y);
}

static void update_load_option(const menu_layout_params_t *params)
{
    if (!params->opt->load_button)
        return;
    config_menu_button(params->opt->load_button, params->scale * 4.75f,
        params->left_margin, params->start_y + params->spacing * 4);
}

static void update_exit_option(const menu_layout_params_t *params)
{
    float centered_x;

    if (params->opt->exit) {
        sfSprite_setScale(params->opt->exit->sprite, (sfVector2f){4.75f *
            params->scale, 4.75f * params->scale});
        centered_x = (params->window_size.x - sfSprite_getGlobalBounds(
            params->opt->exit->sprite).width) / 2.0f;
        sfSprite_setPosition(params->opt->exit->sprite, (sfVector2f){
            centered_x, params->start_y + params->spacing * 5});
        params->opt->exit->bounds = sfSprite_getGlobalBounds(
            params->opt->exit->sprite);
    }
}

static void setup_framerate_label_and_minus(const menu_layout_params_t *params,
    float framerate_y)
{
    if (params->opt->framerate_label)
        config_menu_button(params->opt->framerate_label, params->scale * 4.75f,
            params->left_margin, framerate_y);
    if (params->opt->framerate_minus)
        config_menu_button(params->opt->framerate_minus, params->scale * 1.2f,
            params->minus_x, framerate_y);
}

static float calculate_framerate_text_position(const menu_layout_params_t
    *params)
{
    float consistent_spacing = 30 * params->scale;
    float minus_width = 0;

    if (params->opt->framerate_minus)
        minus_width = sfSprite_getGlobalBounds(
            params->opt->framerate_minus->sprite).width;
    return params->minus_x + minus_width + consistent_spacing;
}

static void setup_framerate_text_buttons(const menu_layout_params_t *params,
    float framerate_y, float percent_x)
{
    for (int i = 0; i < 10; i++) {
        if (params->opt->framerate_text[i])
            config_menu_button(params->opt->framerate_text[i], params->scale *
                1.2f, percent_x, framerate_y);
    }
}

static void setup_framerate_plus_button(const menu_layout_params_t *params)
{
    if (params->opt->framerate_plus) {
        sfSprite_setScale(params->opt->framerate_plus->sprite,
            (sfVector2f){1.2f * params->scale, 1.2f * params->scale});
        position_plus_button(params->opt->framerate_text
            [params->opt->framerate_index], params->opt->framerate_plus);
    }
}

static void update_framerate_options(const menu_layout_params_t *params)
{
    float framerate_y = params->start_y + params->spacing * 3;
    float percent_x;

    setup_framerate_label_and_minus(params, framerate_y);
    percent_x = calculate_framerate_text_position(params);
    setup_framerate_text_buttons(params, framerate_y, percent_x);
    setup_framerate_plus_button(params);
}

void update_options_menu_positions(sfml_t *sfml)
{
    menu_layout_params_t params;

    if (!sfml->menu || !sfml->menu->options)
        return;
    params = (menu_layout_params_t){ .opt = sfml->menu->options,
        .window_size = sfRenderWindow_getSize(sfml->window),
        .scale = get_scale_factor(sfml),
        .left_margin = LEFT_MARGIN * sfml->window_size->scale_factor_x,
        .right_margin = RIGHT_MARGIN * sfml->window_size->scale_factor_x,
        .start_y = START_Y * sfml->window_size->scale_factor_y,
        .spacing = SPACING * sfml->window_size->scale_factor_y,
        .minus_x = 0 };
    params.minus_x = params.window_size.x - params.right_margin - 100 *
    params.scale;
    update_fullscreen_options(&params);
    update_sfx_options(&params);
    update_music_options(&params);
    update_framerate_options(&params);
    update_load_option(&params);
    update_exit_option(&params);
}
