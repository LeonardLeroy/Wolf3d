/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** perform_enemy_ia.c
*/

#include "wolf3d.h"

enemy_ai_manager_t *init_enemy_pathfinding(void)
{
    enemy_ai_manager_t *ai_mgr = salloc(sizeof(enemy_ai_manager_t));

    if (!ai_mgr)
        return NULL;
    for (int i = 0; i < NUM_ENEMIES; i++) {
        ai_mgr->ai_cache[i].state = AI_STATE_DIRECT;
        ai_mgr->ai_cache[i].stuck_counter = 0;
        ai_mgr->ai_cache[i].wall_follow_angle = 0.0f;
        ai_mgr->ai_cache[i].wall_follow_clockwise = 1;
        ai_mgr->ai_cache[i].update_frame = 0;
    }
    ai_mgr->current_frame = 0;
    return ai_mgr;
}

void update_pathfinding_frame(enemy_ai_manager_t *ai_mgr)
{
    ai_mgr->current_frame++;
    if (ai_mgr->current_frame > 10000)
        ai_mgr->current_frame = 0;
}

void cleanup_enemy_pathfinding(enemy_ai_manager_t *ai_mgr)
{
    if (!ai_mgr)
        return;
    free(ai_mgr);
}

static int enemy_can_see_player(sfml_t *sfml, enemy_t *enemy)
{
    player_t *player = sfml->game->player;
    float dx = player->x - enemy->world_x;
    float dy = player->y - enemy->world_y;
    float distance = sqrt(dx * dx + dy * dy);

    if (distance > 300.0f)
        return 0;
    return has_clear_line_of_sight(sfml, (line_t){enemy->world_x,
        enemy->world_y, player->x, player->y});
}

void perform_enemy_ia(sfml_t *sfml, enemy_t *enemy, int enemy_id,
    enemy_ai_manager_t *ai_mgr)
{
    if (enemy->hp <= 0 || enemy->current == enemy->hurt)
        return;
    if (enemy->current == enemy->shoot) {
        handle_enemy_attack(sfml, enemy);
        return;
    }
    if (enemy_can_see_player(sfml, enemy)) {
        attack_player(sfml, enemy);
        if (enemy->current == enemy->walk)
            move_towards_player(sfml, enemy, enemy_id, ai_mgr);
    }
}
