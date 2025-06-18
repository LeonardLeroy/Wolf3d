/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** free_win_lose.c
*/

#include "wolf3d.h"

static void free_win_lose_button(menu_button_t *button)
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

static void free_win_lose_sprites(sfml_t *sfml)
{
    if (sfml->win_lose->result_sprite) {
        sfSprite_destroy(sfml->win_lose->result_sprite);
        sfml->win_lose->result_sprite = NULL;
    }
    if (sfml->win_lose->result_texture) {
        sfTexture_destroy(sfml->win_lose->result_texture);
        sfml->win_lose->result_texture = NULL;
    }
}

static void free_overlays(sfml_t *sfml)
{
    if (sfml->win_lose->flash_overlay) {
        sfRectangleShape_destroy(sfml->win_lose->flash_overlay);
        sfml->win_lose->flash_overlay = NULL;
    }
    if (sfml->win_lose->fade_overlay) {
        sfRectangleShape_destroy(sfml->win_lose->fade_overlay);
        sfml->win_lose->fade_overlay = NULL;
    }
}

void free_win_lose(sfml_t *sfml)
{
    if (!sfml->win_lose)
        return;
    free_win_lose_button(sfml->win_lose->restart_button);
    free_win_lose_button(sfml->win_lose->main_menu_button);
    free_win_lose_button(sfml->win_lose->exit_button);
    free_win_lose_sprites(sfml);
    free_overlays(sfml);
    free(sfml->win_lose);
    sfml->win_lose = NULL;
}
