/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-evan.lafolie
** File description:
** update_saves.c
*/

#include "wolf3d.h"

static void draw_arrows(saves_t *saves, sfml_t *sfml)
{
    if (saves->save_count > 1) {
        if (saves->arrow_left && saves->arrow_left->sprite)
            sfRenderWindow_drawSprite(sfml->window,
                saves->arrow_left->sprite, NULL);
        if (saves->arrow_right && saves->arrow_right->sprite)
            sfRenderWindow_drawSprite(sfml->window,
                saves->arrow_right->sprite, NULL);
    }
}

static void draw_buttons(saves_t *saves, sfml_t *sfml)
{
    if (saves->save_button && saves->save_button->sprite)
        sfRenderWindow_drawSprite(sfml->window, saves->save_button->sprite,
            NULL);
    if (saves->load_button && saves->load_button->sprite)
        sfRenderWindow_drawSprite(sfml->window, saves->load_button->sprite,
            NULL);
    if (saves->back_button && saves->back_button->sprite)
        sfRenderWindow_drawSprite(sfml->window, saves->back_button->sprite,
            NULL);
}

void update_saves(sfml_t *sfml)
{
    saves_t *saves = sfml->menu->saves;

    if (!saves)
        return;
    sfRenderWindow_drawSprite(sfml->window, sfml->menu->bg_sprite, NULL);
    render_color(sfml);
    sfRenderWindow_setView(sfml->window, sfml->game->cameras->camMenu);
    draw_buttons(saves, sfml);
    draw_arrows(saves, sfml);
    for (int i = 0; i < saves->name_sprites_count; i++) {
        if (saves->name_sprites && saves->name_sprites[i])
            sfRenderWindow_drawSprite(sfml->window, saves->name_sprites[i],
                NULL);
    }
}
