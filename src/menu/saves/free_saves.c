/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-evan.lafolie
** File description:
** free_saves.c
*/

#include "wolf3d.h"

static void free_char_sprites(saves_t *saves)
{
    for (int i = 0; i < 12; i++) {
        if (!saves->char_sprites[i])
            continue;
        if (saves->char_sprites[i]->texture)
            sfTexture_destroy(saves->char_sprites[i]->texture);
        if (saves->char_sprites[i]->sprite)
            sfSprite_destroy(saves->char_sprites[i]->sprite);
        free(saves->char_sprites[i]);
    }
}

static void free_menu_button_saves(menu_button_t *button)
{
    if (!button)
        return;
    if (button->texture)
        sfTexture_destroy(button->texture);
    if (button->sprite)
        sfSprite_destroy(button->sprite);
    free(button);
}

static void free_name_sprites(saves_t *saves)
{
    if (!saves->name_sprites)
        return;
    for (int i = 0; i < saves->name_sprites_count; i++) {
        if (saves->name_sprites[i])
            sfSprite_destroy(saves->name_sprites[i]);
    }
    free(saves->name_sprites);
}

static void free_buttons_saves(saves_t *saves)
{
    free_menu_button_saves(saves->save_button);
    free_menu_button_saves(saves->load_button);
    free_menu_button_saves(saves->back_button);
    free_menu_button_saves(saves->arrow_left);
    free_menu_button_saves(saves->arrow_right);
}

void free_saves(sfml_t *sfml)
{
    saves_t *saves;

    if (!sfml->menu || !sfml->menu->saves)
        return;
    saves = sfml->menu->saves;
    if (saves->save_texture)
        sfTexture_destroy(saves->save_texture);
    free_char_sprites(saves);
    free_buttons_saves(saves);
    if (saves->save_files) {
        for (int i = 0; i < saves->save_count; i++)
            free(saves->save_files[i]);
        free(saves->save_files);
    }
    free_name_sprites(saves);
    free(saves);
    sfml->menu->saves = NULL;
}
