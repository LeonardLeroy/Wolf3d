/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** update_win_lose.c
*/

#include "wolf3d.h"

static void create_stats_string(sfml_t *sfml, const char *time_str,
    char *stats_str, size_t size)
{
    snprintf(stats_str, size,
        "Game Time: %s\nEnemies Killed: %d\nRemaining HP: %d%%",
        time_str, sfml->win_lose->enemies_killed,
        sfml->win_lose->remaining_hp);
}

static sfText *create_configured_text(sfml_t *sfml, const char *text_string)
{
    sfText *text = sfText_create();

    sfText_setFont(text, sfml->fonts->doom_ui);
    sfText_setCharacterSize(text, 32 * get_scale_factor(sfml));
    sfText_setString(text, text_string);
    sfText_setColor(text, sfColor_fromRGB(200, 200, 200));
    return text;
}

static void center_text_horizontally(sfml_t *sfml, sfText *text,
    float vertical_position)
{
    sfVector2u window_size = sfRenderWindow_getSize(sfml->window);
    sfFloatRect text_bounds = sfText_getLocalBounds(text);

    sfText_setPosition(text, (sfVector2f){
        (window_size.x - text_bounds.width) / 2,
        vertical_position
    });
}

static void draw_text_with_shadow(sfml_t *sfml, sfText *text)
{
    sfText *shadow_text = sfText_copy(text);
    sfVector2f original_pos = sfText_getPosition(text);

    sfText_setColor(shadow_text, sfColor_fromRGB(0, 0, 0));
    sfText_setPosition(shadow_text, (sfVector2f){
        original_pos.x + 2,
        original_pos.y + 2
    });
    sfRenderWindow_drawText(sfml->window, shadow_text, NULL);
    sfRenderWindow_drawText(sfml->window, text, NULL);
    sfText_destroy(shadow_text);
}

static void draw_statistics(sfml_t *sfml)
{
    char time_str[32];
    char stats_str[256];
    sfText *stats_text;
    sfVector2u window_size;
    int minutes = (int)(sfml->win_lose->game_time / 60);
    int seconds = (int)(sfml->win_lose->game_time) % 60;

    snprintf(time_str, sizeof(time_str), "%02d:%02d", minutes, seconds);
    create_stats_string(sfml, time_str, stats_str, sizeof(stats_str));
    stats_text = create_configured_text(sfml, stats_str);
    window_size = sfRenderWindow_getSize(sfml->window);
    center_text_horizontally(sfml, stats_text, window_size.y * 0.4f);
    draw_text_with_shadow(sfml, stats_text);
    sfText_destroy(stats_text);
}

static void update_flash_phase(sfml_t *sfml)
{
    sfml->win_lose->flash_timer += sfml->clocks->deltaTime;
    if (sfml->win_lose->flash_timer >= 0.3f) {
        sfml->win_lose->transition_phase = 1;
        sfml->win_lose->fade_timer = 0.0f;
    }
}

static void update_fade_phase(sfml_t *sfml)
{
    float fade_progress;

    sfml->win_lose->fade_timer += sfml->clocks->deltaTime;
    fade_progress = sfml->win_lose->fade_timer / 1.0f;
    if (fade_progress > 1.0f)
        fade_progress = 1.0f;
    sfRectangleShape_setFillColor(sfml->win_lose->fade_overlay,
        sfColor_fromRGBA(0, 0, 0, (int)(fade_progress * 200)));
    if (sfml->win_lose->fade_timer >= 1.0f)
        sfml->win_lose->transition_phase = 2;
}

static void draw_menu_phase(sfml_t *sfml)
{
    draw_game(sfml);
    sfRenderWindow_drawRectangleShape(sfml->window,
        sfml->win_lose->fade_overlay, NULL);
    sfRenderWindow_setView(sfml->window, sfml->game->cameras->camHUD);
    sfRenderWindow_drawSprite(sfml->window, sfml->win_lose->result_sprite,
        NULL);
    draw_statistics(sfml);
    sfRenderWindow_drawSprite(sfml->window,
        sfml->win_lose->restart_button->sprite, NULL);
    sfRenderWindow_drawSprite(sfml->window,
        sfml->win_lose->main_menu_button->sprite, NULL);
    sfRenderWindow_drawSprite(sfml->window,
        sfml->win_lose->exit_button->sprite, NULL);
}

static void handle_zero_case(sfml_t *sfml)
{
    update_flash_phase(sfml);
    draw_game(sfml);
    sfRectangleShape_setFillColor(sfml->win_lose->flash_overlay,
        sfColor_fromRGBA(255, 0, 0, (int)(128 *
        (sinf(sfml->win_lose->flash_timer * 15.0f) * 0.5f + 0.5f))));
    sfRenderWindow_drawRectangleShape(sfml->window,
        sfml->win_lose->flash_overlay, NULL);
}

void update_win_lose(sfml_t *sfml)
{
    if (!sfml->win_lose)
        return;
    switch (sfml->win_lose->transition_phase) {
        case 0:
            handle_zero_case(sfml);
            break;
        case 1:
            update_fade_phase(sfml);
            draw_game(sfml);
            sfRenderWindow_drawRectangleShape(sfml->window,
                sfml->win_lose->fade_overlay, NULL);
            break;
        case 2:
            draw_menu_phase(sfml);
            break;
    }
}
