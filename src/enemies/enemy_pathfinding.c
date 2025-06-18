/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-evan.lafolie
** File description:
** enemy_pathfinding.c
*/

#include "wolf3d.h"

void init_wall_following(sfml_t *sfml, enemy_t *enemy, int enemy_id,
    enemy_ai_manager_t *ai_mgr)
{
    float target_angle = calculate_direction_to_player(sfml, enemy);
    float left_angle = target_angle + PI / 2.0f;
    float right_angle = target_angle - PI / 2.0f;
    float left_x = enemy->world_x + cosf(left_angle) * ENEMY_SPEED;
    float left_y = enemy->world_y + sinf(left_angle) * ENEMY_SPEED;
    float right_x = enemy->world_x + cosf(right_angle) * ENEMY_SPEED;
    float right_y = enemy->world_y + sinf(right_angle) * ENEMY_SPEED;

    if (is_position_free(sfml, right_x, right_y)) {
        ai_mgr->ai_cache[enemy_id].wall_follow_angle = right_angle;
        ai_mgr->ai_cache[enemy_id].wall_follow_clockwise = 1;
    } else if (is_position_free(sfml, left_x, left_y)) {
        ai_mgr->ai_cache[enemy_id].wall_follow_angle = left_angle;
        ai_mgr->ai_cache[enemy_id].wall_follow_clockwise = 0;
    } else {
        ai_mgr->ai_cache[enemy_id].wall_follow_angle = target_angle + PI;
        ai_mgr->ai_cache[enemy_id].wall_follow_clockwise = 1;
    }
    ai_mgr->ai_cache[enemy_id].state = AI_STATE_WALL_FOLLOW;
    ai_mgr->ai_cache[enemy_id].stuck_counter = 0;
}

void handle_blocked_movement(enemy_ai_data_t *ai)
{
    float block = ai->wall_follow_clockwise ? PI / 4.0f : - PI / 4.0f;

    ai->wall_follow_angle = normalize_angle(ai->wall_follow_angle + block);
    ai->stuck_counter++;
    if (ai->stuck_counter > 100) {
        ai->state = AI_STATE_SEARCH;
        ai->stuck_counter = 0;
    }
}

void try_wall_following(sfml_t *sfml, enemy_t *enemy, int enemy_id,
    enemy_ai_manager_t *ai_mgr)
{
    enemy_ai_data_t *ai = &ai_mgr->ai_cache[enemy_id];
    float angle = ai->wall_follow_angle;
    float new_x = enemy->world_x + cosf(angle) * ENEMY_SPEED;
    float new_y = enemy->world_y + sinf(angle) * ENEMY_SPEED;
    float free_mvt = ai->wall_follow_clockwise ? - PI / 8.0f : PI / 8.0f;

    if (is_position_free(sfml, new_x, new_y)) {
        update_enemy_position(enemy, new_x, new_y);
        ai->wall_follow_angle = normalize_angle(ai->wall_follow_angle +
            free_mvt);
        if (ai->stuck_counter > 20 && try_direct_movement(sfml, enemy,
            enemy_id, ai_mgr))
            ai->state = AI_STATE_DIRECT;
        ai->stuck_counter++;
    } else
        handle_blocked_movement(ai);
}

int try_search_movement(sfml_t *sfml, enemy_t *enemy, int id,
    enemy_ai_manager_t *ai_mgr)
{
    enemy_ai_data_t *ai = &ai_mgr->ai_cache[id];
    float x = enemy->world_x;
    float y = enemy->world_y;

    for (int i = 0; i < 8; i++) {
        x += cosf(get_dir((id + ai_mgr->current_frame + i) % 8)) * ENEMY_SPEED;
        y += sinf(get_dir((id + ai_mgr->current_frame + i) % 8)) * ENEMY_SPEED;
        if (is_position_free(sfml, x, y)) {
            update_enemy_position(enemy, x, y);
            ai->state = AI_STATE_DIRECT;
            ai->stuck_counter = 0;
            return 1;
        }
    }
    ai->stuck_counter++;
    if (ai->stuck_counter > 50) {
        ai->state = AI_STATE_DIRECT;
        ai->stuck_counter = 0;
    }
    return 0;
}

static void call_state_pathfinding(enemy_ai_data_t *ai, sfml_t *sfml,
    enemy_t *enemy, int enemy_id)
{
    enemy_ai_manager_t *ai_mgr = sfml->game->ai_manager;

    switch (ai->state) {
        case AI_STATE_DIRECT:
            if (!try_direct_movement(sfml, enemy, enemy_id, ai_mgr))
                init_wall_following(sfml, enemy, enemy_id, ai_mgr);
            break;
        case AI_STATE_WALL_FOLLOW:
            try_wall_following(sfml, enemy, enemy_id, ai_mgr);
            break;
        case AI_STATE_SEARCH:
            try_search_movement(sfml, enemy, enemy_id, ai_mgr);
            break;
    }
}

void move_towards_player(sfml_t *sfml, enemy_t *enemy, int enemy_id,
    enemy_ai_manager_t *ai_mgr)
{
    player_t *player = sfml->game->player;
    enemy_ai_data_t *ai = &ai_mgr->ai_cache[enemy_id];
    float dx = enemy->world_x - player->x;
    float dy = enemy->world_y - player->y;
    float distance = sqrtf(dx * dx + dy * dy);

    if ((ai_mgr->current_frame + enemy_id) % 3 != 0)
        return;
    if (distance <= 25.0f)
        return;
    if (distance > 400.0f) {
        ai->state = AI_STATE_DIRECT;
        try_direct_movement(sfml, enemy, enemy_id, ai_mgr);
        return;
    }
    call_state_pathfinding(ai, sfml, enemy, enemy_id);
    ai->update_frame = ai_mgr->current_frame;
}
