/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** precise_enemy_occlusion.c
*/

#include "wolf3d.h"

static precise_enemy_visibility_t get_cached_precise_enemy_visibility(
    sfml_t *sfml, enemy_t *enemy, int id,
    precise_visibility_manager_t *vis_manager)
{
    player_t *player = sfml->game->player;
    precise_visibility_cache_t *cache = &vis_manager->visibility_cache[id];

    if (cache->frame_calculated == vis_manager->current_visibility_frame &&
        fabs(cache->last_player_x - player->x) < 5.0f &&
        fabs(cache->last_player_y - player->y) < 5.0f &&
        fabs(cache->last_player_angle - player->angle) < 0.02f &&
        fabs(cache->last_enemy_x - enemy->world_x) < 2.0f &&
        fabs(cache->last_enemy_y - enemy->world_y) < 2.0f)
        return cache->cached_visibility;
    if (cache->cached_visibility.visibility_mask)
        free(cache->cached_visibility.visibility_mask);
    cache->cached_visibility = calculate_precise_enemy_visibility(sfml, enemy);
    cache->last_player_x = player->x;
    cache->last_player_y = player->y;
    cache->last_player_angle = player->angle;
    cache->last_enemy_x = enemy->world_x;
    cache->last_enemy_y = enemy->world_y;
    cache->frame_calculated = vis_manager->current_visibility_frame;
    return cache->cached_visibility;
}

static sprite_properties_t save_sprite_properties(sfSprite *sprite)
{
    sprite_properties_t props;

    props.original_rect = sfSprite_getTextureRect(sprite);
    props.original_pos = sfSprite_getPosition(sprite);
    props.scale = sfSprite_getScale(sprite);
    return props;
}

static void draw_enemy_with_partial_occlusion(sfml_t *sfml, sfSprite *sprite,
    precise_enemy_visibility_t visibility, sprite_properties_t props)
{
    int ray_count = visibility.end_ray - visibility.start_ray + 1;
    float segment_width = (float)props.original_rect.width / ray_count;
    sfIntRect segment_rect;
    sfVector2f segment_pos;

    for (int i = 0; i < ray_count; i++) {
        if (visibility.visibility_mask[i] > 0.5f) {
            segment_rect.left = props.original_rect.left + (int)(i *
                segment_width);
            segment_rect.top = props.original_rect.top;
            segment_rect.width = (int)segment_width + 1;
            segment_rect.height = props.original_rect.height;
            segment_pos.x = props.original_pos.x + (i * segment_width *
                props.scale.x);
            segment_pos.y = props.original_pos.y;
            sfSprite_setTextureRect(sprite, segment_rect);
            sfSprite_setPosition(sprite, segment_pos);
            sfRenderWindow_drawSprite(sfml->window, sprite, NULL);
        }
    }
}

static void draw_enemy_with_precise_occlusion(sfml_t *sfml, enemy_t *enemy,
    int enemy_id, precise_visibility_manager_t *vis_manager)
{
    precise_enemy_visibility_t visibility =
        get_cached_precise_enemy_visibility(sfml, enemy, enemy_id,
            vis_manager);
    sfSprite *sprite = enemy->current->sprite;
    sprite_properties_t props;

    if (!(visibility.total_visibility > 0.01f))
        return;
    props = save_sprite_properties(sprite);
    if (visibility.total_visibility >= 0.99f) {
        sfRenderWindow_drawSprite(sfml->window, sprite, NULL);
        return;
    }
    draw_enemy_with_partial_occlusion(sfml, sprite, visibility, props);
    sfSprite_setTextureRect(sprite, props.original_rect);
    sfSprite_setPosition(sprite, props.original_pos);
}

static int collect_visible_enemies(sfml_t *sfml,
    enemy_depth_t *visible_enemies, precise_visibility_manager_t *vis_manager)
{
    int visible_count = 0;
    precise_enemy_visibility_t visibility;

    vis_manager->current_visibility_frame++;
    for (int i = 0; i < NUM_ENEMIES; i++) {
        if (!sfml->game->enemies[i]->visible)
            continue;
        visibility = get_cached_precise_enemy_visibility(sfml,
            sfml->game->enemies[i], i, vis_manager);
        if (visibility.total_visibility > 0.01f) {
            visible_enemies[visible_count].enemy = sfml->game->enemies[i];
            visible_enemies[visible_count].distance =
                sfml->game->enemies[i]->distance;
            visible_count++;
        }
    }
    return visible_count;
}

static void sort_enemies_by_distance(enemy_depth_t *visible_enemies,
    int visible_count, int i)
{
    enemy_depth_t temp;

    for (int j = 0; j < visible_count - i - 1; j++) {
        if (visible_enemies[j].distance < visible_enemies[j + 1].distance) {
            temp = visible_enemies[j];
            visible_enemies[j] = visible_enemies[j + 1];
            visible_enemies[j + 1] = temp;
        }
    }
}

static int find_enemy_id(sfml_t *sfml, enemy_t *target_enemy)
{
    for (int i = 0; i < NUM_ENEMIES; i++) {
        if (sfml->game->enemies[i] == target_enemy)
            return i;
    }
    return -1;
}

static void draw_visible_enemies(sfml_t *sfml, enemy_depth_t *visible_enemies,
    int visible_count, precise_visibility_manager_t *vis_manager)
{
    int enemy_id = -1;

    for (int i = 0; i < visible_count; i++) {
        enemy_id = find_enemy_id(sfml, visible_enemies[i].enemy);
        if (enemy_id != -1)
            draw_enemy_with_precise_occlusion(sfml, visible_enemies[i].enemy,
                enemy_id, vis_manager);
    }
}

void draw_enemies_with_precise_occlusion(sfml_t *sfml)
{
    enemy_depth_t visible_enemies[NUM_ENEMIES];
    precise_visibility_manager_t *vis_manager = sfml->game->visibility_manager;
    int visible_count;

    if (!vis_manager)
        return;
    visible_count = collect_visible_enemies(sfml, visible_enemies,
        vis_manager);
    for (int i = 0; i < visible_count - 1; i++)
        sort_enemies_by_distance(visible_enemies, visible_count, i);
    draw_visible_enemies(sfml, visible_enemies, visible_count, vis_manager);
}

void cleanup_precise_visibility_cache(precise_visibility_manager_t *vis_mgn)
{
    if (!vis_mgn)
        return;
    for (int i = 0; i < NUM_ENEMIES; i++) {
        if (vis_mgn->visibility_cache[i].cached_visibility.visibility_mask) {
            free(vis_mgn->visibility_cache[i].cached_visibility.
                visibility_mask);
            vis_mgn->visibility_cache[i].cached_visibility.visibility_mask =
            NULL;
        }
    }
    free(vis_mgn);
}
