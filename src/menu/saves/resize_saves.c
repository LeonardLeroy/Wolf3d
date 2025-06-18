/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-evan.lafolie
** File description:
** resize_saves.c
*/

#include "wolf3d.h"

static void update_save_load_button(sfml_t *sfml, menu_button_t *button,
    float scale, int factor)
{
    if (button && button->sprite) {
        sfSprite_setScale(button->sprite, (sfVector2f){4.75f * scale, 4.75f *
            scale});
        sfSprite_setPosition(button->sprite, (sfVector2f){
            LEFT_MARGIN * sfml->window_size->scale_factor_x,
            factor * sfml->window_size->scale_factor_y});
        button->bounds = sfSprite_getGlobalBounds(button->sprite);
    }
}

static void update_back_button(sfml_t *sfml, saves_t *saves, float scale)
{
    sfVector2u window_size = sfRenderWindow_getSize(sfml->window);

    if (saves->back_button && saves->back_button->sprite) {
        sfSprite_setScale(saves->back_button->sprite, (sfVector2f){4.75f *
            scale, 4.75f * scale});
        sfSprite_setPosition(saves->back_button->sprite, (sfVector2f){
            (window_size.x - sfSprite_getGlobalBounds(
            saves->back_button->sprite).width) / 2.0f, (START_Y + SPACING * 4)
            * sfml->window_size->scale_factor_y});
        saves->back_button->bounds = sfSprite_getGlobalBounds(
            saves->back_button->sprite);
    }
}

void update_saves_menu_positions(sfml_t *sfml)
{
    saves_t *saves;
    float scale;

    if (!sfml->menu || !sfml->menu->saves)
        return;
    saves = sfml->menu->saves;
    scale = get_scale_factor(sfml);
    update_save_load_button(sfml, saves->save_button, scale, START_Y);
    update_save_load_button(sfml, saves->load_button, scale, START_Y +
        SPACING);
    update_back_button(sfml, saves, scale);
    if (saves->arrow_left && saves->arrow_left->sprite)
        sfSprite_setScale(saves->arrow_left->sprite, (sfVector2f){scale * 3.0f,
            scale * 3.0f});
    if (saves->arrow_right && saves->arrow_right->sprite)
        sfSprite_setScale(saves->arrow_right->sprite, (sfVector2f){- scale *
            3.0f, scale * 3.0f});
    create_name_sprites(sfml, saves);
    position_arrows(sfml, saves);
}
