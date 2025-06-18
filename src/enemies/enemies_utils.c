/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-evan.lafolie
** File description:
** enemies_utils.c
*/

#include "wolf3d.h"

relative_pos_t calculate_relative_position(player_t *player,
    enemy_t *enemy)
{
    relative_pos_t pos;

    pos.dx = enemy->world_x - player->x;
    pos.dy = enemy->world_y - player->y;
    pos.distance = sqrt(pos.dx * pos.dx + pos.dy * pos.dy);
    pos.angle = normalize_angle_range(atan2(pos.dy, pos.dx) - player->angle);
    return pos;
}

int check_basic_visibility(relative_pos_t pos)
{
    if (pos.distance < 0.1f || pos.distance > 500.0f)
        return 0;
    if (fabs(pos.angle) > (FOV / 2.0f) + 0.2f)
        return 0;
    return 1;
}

int check_line_of_sight(sfml_t *sfml, player_t *player, enemy_t *enemy)
{
    return has_clear_line_of_sight(sfml, (line_t){
        player->x, player->y, enemy->world_x, enemy->world_y
    });
}

display_props_t calculate_display_properties(sfml_t *sfml,
    enemy_t *enemy, relative_pos_t pos)
{
    display_props_t props;
    sfVector2u window_size = sfRenderWindow_getSize(sfml->window);
    float distance_proj_plane = (window_size.x / 2.0f) / tan(FOV / 2.0f);
    sfIntRect sprite_rect;
    float sprite_width;
    float sprite_height;

    props.screen_x = (window_size.x / 2.0f) + (tan(pos.angle) *
    distance_proj_plane);
    props.scale = (distance_proj_plane / pos.distance) * 0.525f;
    sprite_rect = sfSprite_getTextureRect(enemy->current->sprite);
    sprite_width = sprite_rect.width * props.scale;
    sprite_height = sprite_rect.height * props.scale;
    props.screen_y = (window_size.y / 2.0f) - (sprite_height * 0.215f) +
        sfml->game->player->height_offset;
    props.screen_x -= sprite_width / 2.0f;
    props.brightness = apply_flashlight(sfml, enemy->world_x, enemy->world_y,
        (1.0f / (1.0f + pos.distance * 0.004f)));
    return props;
}
