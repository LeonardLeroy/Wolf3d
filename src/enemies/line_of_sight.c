/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** line_of_sight.c
*/

#include "wolf3d.h"

static visibility_points_t check_enemy_points_visibility(sfml_t *sfml,
    enemy_t *enemy)
{
    visibility_points_t points = {0};
    sfVector2i enemy_size = get_enemy_frame_size(enemy->type);
    float half_width = enemy_size.x / 2.0f;

    points.left_visible = is_point_visible(sfml, enemy->world_x - half_width,
        enemy->world_y);
    points.center_visible = is_point_visible(sfml, enemy->world_x,
        enemy->world_y);
    points.right_visible = is_point_visible(sfml, enemy->world_x + half_width,
        enemy->world_y);
    points.visible_parts = 0.0f;
    if (points.left_visible)
        points.visible_parts += 1.0f;
    if (points.center_visible)
        points.visible_parts += 2.0f;
    if (points.right_visible)
        points.visible_parts += 1.0f;
    return points;
}

static void calculate_visibility_slices(visibility_points_t points,
    enemy_visibility_t *result)
{
    result->left_slice = 4;
    result->right_slice = -1;
    if (points.left_visible) {
        result->left_slice = 0;
        result->right_slice = 0;
    }
    if (points.center_visible) {
        if (result->left_slice == 4)
            result->left_slice = 1;
        result->right_slice = 2;
    }
    if (points.right_visible) {
        if (result->left_slice == 4)
            result->left_slice = 3;
        result->right_slice = 3;
    }
}

static int calculate_slice_count(visibility_points_t points, int left_slice,
    int right_slice)
{
    int slice_count;

    if (right_slice >= left_slice)
        slice_count = right_slice - left_slice + 1;
    else
        slice_count = 0;
    if ((points.left_visible && points.center_visible && !points.right_visible)
    || (!points.left_visible && points.center_visible && points.right_visible))
        slice_count = 3;
    else if (points.left_visible && !points.center_visible &&
        points.right_visible)
        slice_count = 2;
    return slice_count;
}

static enemy_visibility_t calculate_enemy_visibility(sfml_t *sfml,
    enemy_t *enemy)
{
    enemy_visibility_t result = {0};
    visibility_points_t points = check_enemy_points_visibility(sfml, enemy);

    calculate_visibility_slices(points, &result);
    result.total_visibility = points.visible_parts / 4.0f;
    result.slice_count = calculate_slice_count(points, result.left_slice,
        result.right_slice);
    return result;
}

enemy_visibility_t get_enemy_visibility(sfml_t *sfml, enemy_t *enemy,
    int enemy_id)
{
    player_t *player = sfml->game->player;
    visibility_context_t *ctx = &sfml->game->visibility_ctx;
    visibility_cache_t *cached = &ctx->cache[enemy_id];

    if (cached->frame_calculated == ctx->current_frame &&
        fabs(cached->player_x - player->x) < 2.0f &&
        fabs(cached->player_y - player->y) < 2.0f &&
        fabs(cached->enemy_x - enemy->world_x) < 2.0f &&
        fabs(cached->enemy_y - enemy->world_y) < 2.0f) {
        return cached->visibility;
    }
    cached->visibility = calculate_enemy_visibility(sfml, enemy);
    cached->player_x = player->x;
    cached->player_y = player->y;
    cached->player_angle = player->angle;
    cached->enemy_x = enemy->world_x;
    cached->enemy_y = enemy->world_y;
    cached->frame_calculated = ctx->current_frame;
    return cached->visibility;
}

void update_visibility_frame(sfml_t *sfml)
{
    visibility_context_t *ctx = &sfml->game->visibility_ctx;

    ctx->current_frame++;
    if (ctx->current_frame > 1000000)
        ctx->current_frame = 0;
}

int has_clear_line_of_sight(sfml_t *sfml, line_t line)
{
    float dx = line.x2 - line.x1;
    float dy = line.y2 - line.y1;
    float distance = sqrt(dx * dx + dy * dy);
    int steps;
    float current_x = line.x1;
    float current_y = line.y1;

    if (distance < 1.0f)
        return 1;
    steps = (int)(distance / (TILE_SIZE / 4.0f));
    for (int i = 0; i <= steps; i++) {
        if (is_wall(sfml, current_x, current_y))
            return 0;
        current_x += dx / steps;
        current_y += dy / steps;
    }
    return 1;
}

static int has_clean_line(sfml_t *sfml, player_t *player, enemy_t *enemy)
{
    float offset = TILE_SIZE / 4.0f;
    line_t lines[5] = {
        {player->x, player->y, enemy->world_x, enemy->world_y},
        {player->x, player->y, enemy->world_x - offset,
            enemy->world_y - offset},
        {player->x, player->y, enemy->world_x + offset,
            enemy->world_y - offset},
        {player->x, player->y, enemy->world_x - offset,
            enemy->world_y + offset},
        {player->x, player->y, enemy->world_x + offset,
            enemy->world_y + offset}
    };

    for (int i = 0; i < 5; i++) {
        if (has_clear_line_of_sight(sfml, lines[i]))
            return 1;
    }
    return 0;
}

int is_enemy_visible_with_walls(sfml_t *sfml, enemy_t *enemy)
{
    player_t *player = sfml->game->player;
    float dx = enemy->world_x - player->x;
    float dy = enemy->world_y - player->y;
    float distance = sqrt(dx * dx + dy * dy);
    float relative_angle = normalize_angle_range(atan2(dy, dx) -
        player->angle);

    if (distance < 0.1f || distance > 500.0f)
        return 0;
    if (fabs(relative_angle) > (FOV / 2.0f) + 0.2f)
        return 0;
    if (enemy->hp <= 0) {
        if (has_clean_line(sfml, player, enemy))
            return 1;
        return 0;
    } else
        return has_clear_line_of_sight(sfml, (line_t){player->x, player->y,
            enemy->world_x, enemy->world_y});
}

float calculate_enemy_visibility_percentage(sfml_t *sfml, enemy_t *enemy)
{
    float offset = TILE_SIZE / 4.0f;
    int visible_points = 0;
    float check_points[][2] = {
        {enemy->world_x, enemy->world_y},
        {enemy->world_x - offset, enemy->world_y - offset},
        {enemy->world_x, enemy->world_y - offset},
        {enemy->world_x + offset, enemy->world_y - offset},
        {enemy->world_x - offset, enemy->world_y},
        {enemy->world_x + offset, enemy->world_y},
        {enemy->world_x - offset, enemy->world_y + offset},
        {enemy->world_x, enemy->world_y + offset},
        {enemy->world_x + offset, enemy->world_y + offset}
    };

    for (int i = 0; i < 9; i++) {
        if (has_clear_line_of_sight(sfml, (line_t){sfml->game->player->x,
        sfml->game->player->y, check_points[i][0], check_points[i][1]}))
            visible_points++;
    }
    return (float)visible_points / 9;
}
