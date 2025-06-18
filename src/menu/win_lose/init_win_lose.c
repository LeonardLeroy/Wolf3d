/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** init_win_lose.c
*/

#include "wolf3d.h"

static void init_win_lose_buttons(sfml_t *sfml)
{
    float scale = get_scale_factor(sfml);

    sfml->win_lose->restart_button = create_button_with_scale("menu/m_start",
        4.0f * scale);
    sfml->win_lose->main_menu_button = create_button_with_scale(
        "death/main_menu", 4.0f * scale);
    sfml->win_lose->exit_button = create_button_with_scale("menu/m_exit",
        4.0f * scale);
    update_win_lose_buttons_positions(sfml);
}

static void init_overlays(sfml_t *sfml)
{
    sfVector2u window_size = sfRenderWindow_getSize(sfml->window);

    sfml->win_lose->flash_overlay = sfRectangleShape_create();
    sfRectangleShape_setSize(sfml->win_lose->flash_overlay,
        (sfVector2f){window_size.x, window_size.y});
    sfRectangleShape_setFillColor(sfml->win_lose->flash_overlay,
        sfColor_fromRGBA(255, 0, 0, 128));
    sfml->win_lose->fade_overlay = sfRectangleShape_create();
    sfRectangleShape_setSize(sfml->win_lose->fade_overlay,
        (sfVector2f){window_size.x, window_size.y});
    sfRectangleShape_setFillColor(sfml->win_lose->fade_overlay,
        sfColor_fromRGBA(0, 0, 0, 0));
}

void init_win_lose(sfml_t *sfml)
{
    sfml->win_lose = salloc(sizeof(win_lose_t));
    memset(sfml->win_lose, 0, sizeof(win_lose_t));
    sfml->win_lose->flash_timer = 0.0f;
    sfml->win_lose->fade_timer = 0.0f;
    sfml->win_lose->transition_phase = 0;
    init_overlays(sfml);
    init_win_lose_buttons(sfml);
    update_win_lose_positions(sfml);
}

static void init_lose_display(sfml_t *sfml)
{
    float scale;

    sfml->win_lose->is_win = 0;
    sfml->win_lose->game_time = sfml->clocks->elapsed;
    sfml->win_lose->enemies_killed = sfml->game->player->frags;
    sfml->win_lose->remaining_hp = 0;
    sfml->win_lose->result_texture = sfTexture_createFromFile(image(
        "death/be_better"), NULL);
    sfml->win_lose->result_sprite = sfSprite_create();
    sfSprite_setTexture(sfml->win_lose->result_sprite,
        sfml->win_lose->result_texture, sfTrue);
    scale = get_scale_factor(sfml);
    sfSprite_setScale(sfml->win_lose->result_sprite,
        (sfVector2f){scale * 3.0f, scale * 3.0f});
    sfSprite_setPosition(sfml->win_lose->result_sprite, (sfVector2f){
        get_centered_x(sfml, sfml->win_lose->result_sprite), 50 * scale});
    sfml->win_lose->flash_timer = 0.0f;
    sfml->win_lose->fade_timer = 0.0f;
    sfml->win_lose->transition_phase = 0;
}

void trigger_game_lose(sfml_t *sfml)
{
    if (!sfml->win_lose)
        init_win_lose(sfml);
    init_lose_display(sfml);
    switch_state(sfml, (switch_state_args_t){WIN_LOSE, &update_win_lose,
        &events_win_lose});
    sfRenderWindow_setMouseCursorVisible(sfml->window, 1);
}
