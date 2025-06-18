/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-evan.lafolie
** File description:
** music_options.c
*/

#include "wolf3d.h"

static void setup_sfx_volume_texts(const menu_layout_params_t *params,
    float sfx_y)
{
    float consistent_spacing = 30 * params->scale;
    float percent_x = params->minus_x + (params->opt->sfx_minus ?
        sfSprite_getGlobalBounds(params->opt->sfx_minus->sprite).width : 0) +
        consistent_spacing;

    for (int i = 0; i <= 10; i++) {
        if (params->opt->sfx_volume_text[i])
            config_menu_button(params->opt->sfx_volume_text[i], params->scale *
                1.2f, percent_x, sfx_y);
    }
}

void update_sfx_options(const menu_layout_params_t *params)
{
    float sfx_y = params->start_y + params->spacing;

    if (params->opt->sfx_label)
        config_menu_button(params->opt->sfx_label, params->scale * 4.75f,
            params->left_margin, sfx_y);
    if (params->opt->sfx_minus)
        config_menu_button(params->opt->sfx_minus, params->scale * 1.2f,
            params->minus_x, sfx_y);
    setup_sfx_volume_texts(params, sfx_y);
    if (params->opt->sfx_plus) {
        sfSprite_setScale(params->opt->sfx_plus->sprite, (sfVector2f){1.2f *
            params->scale, 1.2f * params->scale});
        position_plus_button(params->opt->sfx_volume_text
            [params->opt->sfx_volume], params->opt->sfx_plus);
    }
}

static void setup_music_volume_texts(const menu_layout_params_t *params,
    float music_y)
{
    float consistent_spacing = 30 * params->scale;
    float percent_x = params->minus_x + (params->opt->music_minus ?
        sfSprite_getGlobalBounds(params->opt->music_minus->sprite).width : 0) +
        consistent_spacing;

    for (int i = 0; i <= 10; i++) {
        if (params->opt->music_volume_text[i])
            config_menu_button(params->opt->music_volume_text[i],
                params->scale * 1.2f, percent_x, music_y);
    }
}

void update_music_options(const menu_layout_params_t *params)
{
    float music_y = params->start_y + params->spacing * 2;

    if (params->opt->music_label)
        config_menu_button(params->opt->music_label,
            params->scale * 4.75f, params->left_margin, music_y);
    if (params->opt->music_minus)
        config_menu_button(params->opt->music_minus, params->scale * 1.2f,
            params->minus_x, music_y);
    setup_music_volume_texts(params, music_y);
    if (params->opt->music_plus) {
        sfSprite_setScale(params->opt->music_plus->sprite,
            (sfVector2f){1.2f * params->scale, 1.2f * params->scale});
        position_plus_button(params->opt->music_volume_text
            [params->opt->music_volume], params->opt->music_plus);
    }
}

static void create_volume_elements(volume_controls_params_t *params)
{
    const char *volume_names[] = {
        "options/zero", "options/ten", "options/twenty", "options/thirty",
        "options/forty", "options/fifty", "options/sixty", "options/seventy",
        "options/eighty", "options/ninety", "options/hundred"
    };

    *(params->label) = create_button_with_scale(params->label_name, 4.75);
    *(params->minus) = create_button_with_scale("options/o_minus", 1.2);
    *(params->plus) = create_button_with_scale("options/o_plus", 1.2);
    for (int i = 0; i <= 10; i++)
        params->volume_text[i] = create_button_with_scale(volume_names[i],
            1.2);
}

static void position_volume_elements(sfml_t *sfml,
    volume_controls_params_t *params)
{
    sfVector2u window_size = sfRenderWindow_getSize(sfml->window);
    float minus_x = window_size.x - RIGHT_MARGIN - 100;
    float consistent_spacing = 30;
    float percent_x = minus_x + sfSprite_getGlobalBounds(
        (*(params->minus))->sprite).width + consistent_spacing;

    sfSprite_setPosition((*(params->label))->sprite,
        (sfVector2f){LEFT_MARGIN, params->y_position});
    sfSprite_setPosition((*(params->minus))->sprite,
        (sfVector2f){minus_x, params->y_position});
    for (int i = 0; i <= 10; i++) {
        sfSprite_setPosition(params->volume_text[i]->sprite,
            (sfVector2f){percent_x, params->y_position});
        params->volume_text[i]->bounds = sfSprite_getGlobalBounds(
            params->volume_text[i]->sprite);
    }
}

static void finalize_volume_controls(volume_controls_params_t *params)
{
    *(params->volume_value) = 5;
    position_plus_button(params->volume_text[*(params->volume_value)],
        *(params->plus));
    (*(params->label))->bounds = sfSprite_getGlobalBounds(
        (*(params->label))->sprite);
    (*(params->minus))->bounds = sfSprite_getGlobalBounds(
        (*(params->minus))->sprite);
    (*(params->plus))->bounds = sfSprite_getGlobalBounds(
        (*(params->plus))->sprite);
}

static void init_volume_controls(sfml_t *sfml,
    volume_controls_params_t *params)
{
    create_volume_elements(params);
    position_volume_elements(sfml, params);
    finalize_volume_controls(params);
}

void init_volume_options(sfml_t *sfml)
{
    volume_controls_params_t sfx_params = {
        .label = &sfml->menu->options->sfx_label,
        .minus = &sfml->menu->options->sfx_minus,
        .plus = &sfml->menu->options->sfx_plus,
        .volume_text = sfml->menu->options->sfx_volume_text,
        .label_name = "options/o_sfx", .y_position = START_Y + SPACING,
        .volume_value = &sfml->menu->options->sfx_volume,
    };
    volume_controls_params_t music_params = {
        .label = &sfml->menu->options->music_label,
        .minus = &sfml->menu->options->music_minus,
        .plus = &sfml->menu->options->music_plus,
        .volume_text = sfml->menu->options->music_volume_text,
        .label_name = "options/o_music", .y_position = START_Y + SPACING * 2,
        .volume_value = &sfml->menu->options->music_volume,
    };

    init_volume_controls(sfml, &sfx_params);
    init_volume_controls(sfml, &music_params);
}
