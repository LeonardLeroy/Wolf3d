/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-evan.lafolie
** File description:
** enemy_movement.c
*/

#include "wolf3d.h"

float get_dir(int index)
{
    float directions[8] = { 0.0f, PI / 4.0f, PI / 2.0f, 3 * PI / 4.0f, PI,
        5 * PI / 4.0f, 3 * PI / 2.0f, 7 * PI / 4.0f };

    return (float)directions[index];
}

int is_position_free(sfml_t *sfml, float x, float y)
{
    return !will_collide_with_wall(sfml, x, y) &&
        !will_collide_with_enemy(sfml, x, y);
}

float calculate_direction_to_player(sfml_t *sfml, enemy_t *enemy)
{
    player_t *player = sfml->game->player;
    float dx = player->x - enemy->world_x;
    float dy = player->y - enemy->world_y;

    return atan2f(dy, dx);
}

void update_enemy_position(enemy_t *enemy, float new_x, float new_y)
{
    enemy->world_x = new_x;
    enemy->world_y = new_y;
    enemy->x = enemy->world_x;
    enemy->y = enemy->world_y;
}

int try_direct_movement(sfml_t *sfml, enemy_t *enemy, int enemy_id,
    enemy_ai_manager_t *ai_mgr)
{
    float target_angle = calculate_direction_to_player(sfml, enemy);
    float new_x = enemy->world_x + cosf(target_angle) * ENEMY_SPEED;
    float new_y = enemy->world_y + sinf(target_angle) * ENEMY_SPEED;

    if (is_position_free(sfml, new_x, new_y)) {
        enemy->world_x = new_x;
        enemy->world_y = new_y;
        enemy->x = enemy->world_x;
        enemy->y = enemy->world_y;
        ai_mgr->ai_cache[enemy_id].state = AI_STATE_DIRECT;
        ai_mgr->ai_cache[enemy_id].stuck_counter = 0;
        return 1;
    }
    return 0;
}
