/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** update_enemies.c
*/

#include "wolf3d.h"

static void apply_sprite_transforms(enemy_t *enemy, display_props_t props)
{
    sfSprite_setPosition(enemy->current->sprite,
        (sfVector2f){props.screen_x, props.screen_y});
    sfSprite_setScale(enemy->current->sprite,
        (sfVector2f){props.scale, props.scale});
    sfSprite_setColor(enemy->current->sprite,
        sfColor_fromRGB(255 * props.brightness,
        255 * props.brightness, 255 * props.brightness));
}

static void update_enemy_display_data(enemy_t *enemy, relative_pos_t pos,
    display_props_t props)
{
    enemy->distance = pos.distance;
    enemy->screen_x = props.screen_x;
    enemy->screen_y = props.screen_y;
    enemy->scale = props.scale;
}

static void update_enemy_pos(sfml_t *sfml, enemy_t *enemy)
{
    player_t *player = sfml->game->player;
    display_props_t props;
    relative_pos_t pos;

    enemy->visible = 0;
    pos = calculate_relative_position(player, enemy);
    if (!check_basic_visibility(pos))
        return;
    if (!check_line_of_sight(sfml, player, enemy)) {
        enemy->visible = 0;
        return;
    }
    enemy->visible = 1;
    props = calculate_display_properties(sfml, enemy, pos);
    update_enemy_display_data(enemy, pos, props);
    apply_sprite_transforms(enemy, props);
}

void update_enemy(sfml_t *sfml, enemy_t *enemy)
{
    update_enemy_pos(sfml, enemy);
    if (enemy->current == enemy->death &&
        enemy->current->current_frame == enemy->current->frames - 1)
        return;
    enemy->current->anim_timer += sfml->clocks->deltaTime;
    if (enemy->current->anim_timer >= FRAME_DURATION) {
        enemy->current->anim_timer -= FRAME_DURATION;
        if (enemy->hp <= 0) {
            handle_enemy_death(enemy);
            return;
        }
        update_enemy_anims(enemy);
        enemy_grunt(sfml, enemy);
    }
}

static int get_visible_enemies(sfml_t *sfml,
    enemy_distance_t *enemies_by_distance)
{
    int visible_count = 0;
    float distance;

    for (int i = 0; i < NUM_ENEMIES; i++) {
        distance = calculate_enemy_distance(sfml->game->enemies[i],
            sfml->game->player);
        if (distance < 500.0f) {
            enemies_by_distance[visible_count].enemy = sfml->game->enemies[i];
            enemies_by_distance[visible_count].index = i;
            enemies_by_distance[visible_count].distance = distance;
            visible_count++;
        }
    }
    return visible_count;
}

static void sort_enemies_by_distance(enemy_distance_t *enemies_by_distance,
    int count)
{
    int j;
    enemy_distance_t key;

    for (int i = 1; i < count; i++) {
        key = enemies_by_distance[i];
        j = i - 1;
        while (j >= 0 && enemies_by_distance[j].distance > key.distance) {
            enemies_by_distance[j + 1] = enemies_by_distance[j];
            j--;
        }
        enemies_by_distance[j + 1] = key;
    }
}

static void update_visible_enemies(sfml_t *sfml,
    enemy_distance_t *enemies_by_distance, int visible_count)
{
    for (int i = 0; i < visible_count; i++) {
        update_enemy_pos(sfml, enemies_by_distance[i].enemy);
        update_enemy(sfml, enemies_by_distance[i].enemy);
    }
}

static void update_distant_enemies(sfml_t *sfml)
{
    float distance;

    for (int i = 0; i < NUM_ENEMIES; i++) {
        distance = calculate_enemy_distance(sfml->game->enemies[i],
            sfml->game->player);
        if (distance >= 500.0f) {
            update_enemy_pos(sfml, sfml->game->enemies[i]);
            update_enemy(sfml, sfml->game->enemies[i]);
        }
    }
}

void update_enemies(sfml_t *sfml, enemy_ai_manager_t *ai_mgr)
{
    static float last_update = 0.0f;
    enemy_distance_t enemies_by_distance[NUM_ENEMIES];
    int visible_count = 0;

    update_pathfinding_frame(ai_mgr);
    last_update += sfml->clocks->deltaTime;
    if (last_update >= GAME_TIC) {
        for (int i = 0; i < NUM_ENEMIES; i++)
            perform_enemy_ia(sfml, sfml->game->enemies[i], i, ai_mgr);
    }
    visible_count = get_visible_enemies(sfml, enemies_by_distance);
    sort_enemies_by_distance(enemies_by_distance, visible_count);
    update_visible_enemies(sfml, enemies_by_distance, visible_count);
    update_distant_enemies(sfml);
    if (last_update >= GAME_TIC)
        last_update = 0.0f;
}
