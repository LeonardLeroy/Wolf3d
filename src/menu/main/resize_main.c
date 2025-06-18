/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-evan.lafolie
** File description:
** resize_main.c
*/

#include "wolf3d.h"

static void setup_doom_logo(sfml_t *sfml, float scale)
{
    if (!sfml->menu->doom_sprite)
        return;
    sfSprite_setScale(sfml->menu->doom_sprite, (sfVector2f){4.75f *
        scale, 5.75f * scale});
    sfSprite_setPosition(sfml->menu->doom_sprite,
        (sfVector2f){get_centered_x(sfml, sfml->menu->doom_sprite) - 5 *
            scale, 10 * scale});
}

static void setup_skull_sprite(sfml_t *sfml, float scale)
{
    if (!sfml->menu->skull_sheet)
        return;
    sfSprite_setScale(sfml->menu->skull_sheet->sprite,
        (sfVector2f){3.5f * scale, 4.0f * scale});
}

static void setup_menu_button(sfSprite *sprite, sfFloatRect *bounds,
    sfVector2f scale, sfVector2f position)
{
    if (!sprite)
        return;
    sfSprite_setScale(sprite, scale);
    sfSprite_setPosition(sprite, position);
    if (bounds)
        *bounds = sfSprite_getGlobalBounds(sprite);
}

static void setup_start_button(sfml_t *sfml, float scale)
{
    sfVector2f scale_vec = {4.6f * scale, 5.0f * scale};
    sfVector2f position;

    if (!sfml->menu->start_b || !sfml->menu->doom_sprite)
        return;
    position = (sfVector2f){
        sfSprite_getPosition(sfml->menu->doom_sprite).x + 5 * scale,
        450 * sfml->window_size->scale_factor_y
    };
    setup_menu_button(sfml->menu->start_b->sprite,
        &sfml->menu->start_b->bounds, scale_vec, position);
}

static void setup_options_button(sfml_t *sfml, float scale)
{
    sfVector2f scale_vec = {4.6f * scale, 5.0f * scale};
    sfVector2f position;

    if (!sfml->menu->options_b || !sfml->menu->doom_sprite)
        return;
    position = (sfVector2f){
        sfSprite_getPosition(sfml->menu->doom_sprite).x + 5 * scale,
        (450 + 120) * sfml->window_size->scale_factor_y
    };
    setup_menu_button(sfml->menu->options_b->sprite,
        &sfml->menu->options_b->bounds, scale_vec, position);
}

static void setup_exit_button(sfml_t *sfml, float scale)
{
    sfVector2f scale_vec = {4.6f * scale, 5.0f * scale};
    sfVector2f position;

    if (!sfml->menu->exit_b || !sfml->menu->doom_sprite)
        return;
    position = (sfVector2f){
        sfSprite_getPosition(sfml->menu->doom_sprite).x + 5 * scale,
        (450 + 240) * sfml->window_size->scale_factor_y
    };
    setup_menu_button(sfml->menu->exit_b->sprite, &sfml->menu->exit_b->bounds,
        scale_vec, position);
}

static void setup_back_button(sfml_t *sfml, float scale)
{
    sfVector2f scale_vec = {3.5f * scale, 3.5f * scale};

    if (!sfml->menu->back_b)
        return;
    sfSprite_setScale(sfml->menu->back_b->sprite, scale_vec);
    sfml->menu->back_b->bounds = sfSprite_getGlobalBounds(
        sfml->menu->back_b->sprite);
}

static void position_skull_relative_to_start(sfml_t *sfml, float scale)
{
    sfVector2f position;

    if (!sfml->menu->skull_sheet || !sfml->menu->start_b)
        return;
    position = (sfVector2f){
        sfSprite_getPosition(sfml->menu->start_b->sprite).x - 100 * scale,
        sfSprite_getPosition(sfml->menu->start_b->sprite).y
    };
    sfSprite_setPosition(sfml->menu->skull_sheet->sprite, position);
}

void update_main_menu_positions(sfml_t *sfml)
{
    float scale = get_scale_factor(sfml);

    if (!sfml->menu || !sfml->menu->doom_sprite)
        return;
    setup_doom_logo(sfml, scale);
    setup_skull_sprite(sfml, scale);
    setup_start_button(sfml, scale);
    setup_options_button(sfml, scale);
    setup_exit_button(sfml, scale);
    setup_back_button(sfml, scale);
    position_skull_relative_to_start(sfml, scale);
}
