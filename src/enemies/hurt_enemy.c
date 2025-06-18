/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** hurt_enemy.c
*/

#include "wolf3d.h"

static void display_win_screen(sfml_t *sfml)
{
    float scale;

    sfml->win_lose->result_texture = sfTexture_createFromFile(image("you_win"),
    NULL);
    sfml->win_lose->result_sprite = sfSprite_create();
    sfSprite_setTexture(sfml->win_lose->result_sprite,
        sfml->win_lose->result_texture, sfTrue);
    scale = get_scale_factor(sfml);
    sfSprite_setScale(sfml->win_lose->result_sprite, (sfVector2f){scale * 3.0f,
        scale * 3.0f});
    sfSprite_setPosition(sfml->win_lose->result_sprite,
        (sfVector2f){get_centered_x(sfml, sfml->win_lose->result_sprite), 50 *
            scale});
    switch_state(sfml, (switch_state_args_t){WIN_LOSE, &update_win_lose,
        &events_win_lose});
    sfRenderWindow_setMouseCursorVisible(sfml->window, 1);
}

void trigger_game_win(sfml_t *sfml)
{
    if (!sfml->win_lose)
        init_win_lose(sfml);
    sfml->win_lose->is_win = 1;
    sfml->win_lose->game_time = sfml->clocks->elapsed;
    sfml->win_lose->enemies_killed = sfml->game->player->frags;
    sfml->win_lose->remaining_hp = sfml->game->player->hp;
    sfml->win_lose->flash_timer = 0.0f;
    sfml->win_lose->fade_timer = 0.0f;
    sfml->win_lose->transition_phase = 0;
    display_win_screen(sfml);
}

void hurt_enemy(sfml_t *sfml, enemy_t *enemy)
{
    enemy->hp -= 10;
    if (enemy->hp <= 0) {
        enemy->hp = 0;
        sfml->game->player->frags++;
        play_sound(sfml, (enemy->type == IMP) ? "imp_death" : "zombie_death",
            75);
        enemy->current = enemy->death;
        enemy->current->anim_timer = 0.0f;
        set_current_frame(enemy->current, 0);
        if (sfml->game->player->frags == NUM_ENEMIES)
            trigger_game_win(sfml);
        return;
    }
    play_sound(sfml, (enemy->type == IMP) ? "imp_pain" : "zombie_pain", 75);
    enemy->current = enemy->hurt;
    enemy->current->anim_timer = 0.0f;
    set_current_frame(enemy->current, 0);
}
