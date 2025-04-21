/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** render_walls.c
*/

#include "wolf3d.h"

static float calculate_perpendicular_distance(game_t *game, int ray_index)
{
    return game->rays[ray_index].distance *
        cos(game->rays[ray_index].angle - game->player->angle);
}

static float calculate_projected_wall_height(float perpendicular_distance,
    float window_height)
{
    float distance_proj_plane = (window_height / 2) / tan(FOV / 2);

    return (TILE_SIZE / perpendicular_distance) * distance_proj_plane;
}

static sfColor determine_wall_color(ray_t *ray)
{
    if (ray->wall_hit_content == 1) {
        return ray->was_hit_vertical ? sfColor_fromRGB(180, 0, 0)
            : sfColor_fromRGB(200, 0, 0);
    }
    return sfColor_fromRGB(150, 150, 150);
}

static void render_wall_strip(sfml_t *sfml, wall_strip_params_t params)
{
    sfRectangleShape *wall_strip = sfRectangleShape_create();
    sfColor color;

    sfRectangleShape_setSize(wall_strip,
        (sfVector2f){params.strip_width + 1, params.height});
    sfRectangleShape_setPosition(wall_strip,
        (sfVector2f){params.index * params.strip_width, params.top_pixel});
    color = determine_wall_color(&sfml->game->rays[params.index]);
    sfRectangleShape_setFillColor(wall_strip, color);
    sfRenderWindow_drawRectangleShape(sfml->window, wall_strip, NULL);
    sfRectangleShape_destroy(wall_strip);
}

void render_wall_columns(sfml_t *sfml)
{
    sfVector2u window_size = sfRenderWindow_getSize(sfml->window);
    float strip_width = (float)window_size.x / NUM_RAYS;
    wall_strip_params_t params;

    for (int i = 0; i < NUM_RAYS; i++) {
        if (sfml->game->rays[i].distance == FLT_MAX)
            continue;
        params.index = i;
        params.strip_width = strip_width;
        params.height = calculate_projected_wall_height(
            calculate_perpendicular_distance(sfml->game, i), window_size.y);
        params.top_pixel = (window_size.y / 2) - (params.height / 2);
        render_wall_strip(sfml, params);
    }
}

void render_walls(sfml_t *sfml)
{
    render_ceiling(sfml);
    render_floor(sfml);
    render_wall_columns(sfml);
}
