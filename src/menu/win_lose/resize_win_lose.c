/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** resize_win_lose.c
*/

#include "wolf3d.h"

static void update_win_lose_overlays(sfml_t *sfml)
{
    sfVector2u window_size;

    if (!sfml->win_lose)
        return;
    window_size = sfRenderWindow_getSize(sfml->window);
    if (sfml->win_lose->flash_overlay)
        sfRectangleShape_setSize(sfml->win_lose->flash_overlay,
            (sfVector2f){window_size.x, window_size.y});
    if (sfml->win_lose->fade_overlay)
        sfRectangleShape_setSize(sfml->win_lose->fade_overlay,
            (sfVector2f){window_size.x, window_size.y});
}

static void update_win_lose_result_sprite(sfml_t *sfml)
{
    float scale;

    if (!sfml->win_lose || !sfml->win_lose->result_sprite)
        return;
    scale = get_scale_factor(sfml);
    sfSprite_setScale(sfml->win_lose->result_sprite,
        (sfVector2f){scale * 3.0f, scale * 3.0f});
    sfSprite_setPosition(sfml->win_lose->result_sprite,
        (sfVector2f){get_centered_x(sfml, sfml->win_lose->result_sprite),
        50 * scale});
}

static void update_single_button_position(menu_button_t *button, float scale,
    float window_width, float y_position)
{
    if (!button || !button->sprite)
        return;
    sfSprite_setScale(button->sprite, (sfVector2f){4.0f * scale, 4.0f *
        scale});
    sfSprite_setPosition(button->sprite, (sfVector2f){
        (window_width - sfSprite_getGlobalBounds(button->sprite).width) / 2,
        y_position
    });
    button->bounds = sfSprite_getGlobalBounds(button->sprite);
}

void update_win_lose_buttons_positions(sfml_t *sfml)
{
    float scale = get_scale_factor(sfml);
    sfVector2u window_size = sfRenderWindow_getSize(sfml->window);
    float start_y = window_size.y * 0.65f;
    float button_spacing = 80.0f * scale;

    update_single_button_position(sfml->win_lose->restart_button, scale,
        window_size.x, start_y);
    update_single_button_position(sfml->win_lose->main_menu_button, scale,
        window_size.x, start_y + button_spacing);
    update_single_button_position(sfml->win_lose->exit_button, scale,
        window_size.x, start_y + (button_spacing * 2));
}

void update_win_lose_positions(sfml_t *sfml)
{
    if (!sfml->win_lose)
        return;
    update_win_lose_overlays(sfml);
    update_win_lose_result_sprite(sfml);
    update_win_lose_buttons_positions(sfml);
}
