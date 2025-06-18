/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-evan.lafolie
** File description:
** utils_enemies.c
*/

#include "wolf3d.h"

void handle_enemy_death(enemy_t *enemy)
{
    if (enemy->current != enemy->death) {
        enemy->current = enemy->death;
        enemy->current->anim_timer = 0.0f;
        set_current_frame(enemy->current, 0);
    } else
        set_current_frame(enemy->current,
            enemy->current->current_frame + 1);
}

float calculate_enemy_distance(enemy_t *enemy, player_t *player)
{
    float dx = enemy->world_x - player->x;
    float dy = enemy->world_y - player->y;

    return sqrt(dx * dx + dy * dy);
}

int is_point_visible(sfml_t *sfml, float x, float y)
{
    return has_clear_line_of_sight(sfml, (line_t){
        sfml->game->player->x, sfml->game->player->y, x, y
    });
}

static enemy_position_data_t calculate_enemy_pos(player_t *player,
    enemy_t *enemy)
{
    enemy_position_data_t pos_data;

    pos_data.dx = enemy->world_x - player->x;
    pos_data.dy = enemy->world_y - player->y;
    pos_data.distance = sqrtf(pos_data.dx * pos_data.dx + pos_data.dy
        * pos_data.dy);
    pos_data.relative_angle = normalize_angle_range(atan2f(pos_data.dy,
        pos_data.dx) - player->angle);
    return pos_data;
}

static float calculate_angular_size(enemy_t *enemy, float distance)
{
    sfVector2i enemy_size = get_enemy_frame_size(enemy->type);

    return atan2f((enemy_size.x * enemy->scale) / 2.0f, distance);
}

static ray_indices_t calculate_ray_indices(float relative_angle,
    float angular_size)
{
    ray_indices_t indices;
    int temp;
    float left_angle = relative_angle - angular_size;
    float right_angle = relative_angle + angular_size;

    indices.left_ray = (int)((left_angle + FOV / 2.0f) * NUM_RAYS / FOV);
    indices.right_ray = (int)((right_angle + FOV / 2.0f) * NUM_RAYS / FOV);
    indices.left_ray = fmaxf(0, fminf(NUM_RAYS - 1, indices.left_ray));
    indices.right_ray = fmaxf(0, fminf(NUM_RAYS - 1, indices.right_ray));
    if (indices.left_ray > indices.right_ray) {
        temp = indices.left_ray;
        indices.left_ray = indices.right_ray;
        indices.right_ray = temp;
    }
    indices.ray_count = indices.right_ray - indices.left_ray + 1;
    return indices;
}

static float *calculate_mask(sfml_t *sfml, ray_indices_t indices,
    float enemy_distance, int *visible_count)
{
    float *visibility_mask;
    ray_t *ray;

    if (indices.ray_count <= 0) {
        *visible_count = 0;
        return NULL;
    }
    visibility_mask = salloc(indices.ray_count * sizeof(float));
    *visible_count = 0;
    for (int i = indices.left_ray; i <= indices.right_ray; i++) {
        ray = &sfml->game->rays[i];
        if (ray->distance < enemy_distance - 10.0f)
            visibility_mask[i - indices.left_ray] = 0.0f;
        else {
            visibility_mask[i - indices.left_ray] = 1.0f;
            (*visible_count)++;
        }
    }
    return visibility_mask;
}

precise_enemy_visibility_t calculate_precise_enemy_visibility(sfml_t *sfml,
    enemy_t *enemy)
{
    precise_enemy_visibility_t visibility = {0};
    enemy_position_data_t pos_data = calculate_enemy_pos(sfml->game->player,
        enemy);
    ray_indices_t ind;
    int visible_count;
    float *vis_mask;

    if (!(fabs(pos_data.relative_angle) <= FOV / 2.0f))
        return visibility;
    ind = calculate_ray_indices(pos_data.relative_angle,
        calculate_angular_size(enemy, pos_data.distance));
    if (ind.ray_count <= 0)
        return visibility;
    vis_mask = calculate_mask(sfml, ind, pos_data.distance, &visible_count);
    visibility.start_ray = ind.left_ray;
    visibility.end_ray = ind.right_ray;
    visibility.visibility_mask = vis_mask;
    visibility.visible_rays = visible_count;
    visibility.total_visibility = (float)visible_count / ind.ray_count;
    return visibility;
}
