/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** free_menu.c
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
    button = NULL;
}

static void free_menu_textures(sfml_t *sfml)
{
    if (sfml->menu->bg_texture) {
        sfTexture_destroy(sfml->menu->bg_texture);
        sfml->menu->bg_texture = NULL;
    }
    if (sfml->menu->bg_sprite) {
        sfSprite_destroy(sfml->menu->bg_sprite);
        sfml->menu->bg_sprite = NULL;
    }
    if (sfml->menu->doom_texture) {
        sfTexture_destroy(sfml->menu->doom_texture);
        sfml->menu->doom_texture = NULL;
    }
    if (sfml->menu->doom_sprite) {
        sfSprite_destroy(sfml->menu->doom_sprite);
        sfml->menu->doom_sprite = NULL;
    }
}

static void free_menu_buttons(sfml_t *sfml)
{
    free_menu_button(sfml->menu->start_b);
    free_menu_button(sfml->menu->options_b);
    free_menu_button(sfml->menu->exit_b);
    free_menu_button(sfml->menu->back_b);
    free_sprite_sheet(sfml->menu->skull_sheet);
    sfml->menu->skull_sheet = NULL;
}

void free_menu(sfml_t *sfml)
{
    free_options(sfml);
    if (!sfml->menu)
        return;
    free_menu_textures(sfml);
    free_menu_buttons(sfml);
    free_saves(sfml);
    free(sfml->menu);
}
