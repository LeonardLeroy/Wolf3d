/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** render_surfaces.c
*/

#include "wolf3d.h"

static float calculate_projected_wall_height(float perpendicular_distance,
    float window_height)
{
    float distance_proj_plane = (window_height / 2) / tan(FOV / 2);

    return (TILE_SIZE / perpendicular_distance) * distance_proj_plane;
}

static void calculate_ray_directions(player_t *player,
    floor_render_params_t *params)
{
    float left_angle = normalize_angle(player->angle - FOV / 2);
    float right_angle = normalize_angle(player->angle + FOV / 2);

    params->ray_dir_x0 = cos(left_angle);
    params->ray_dir_y0 = sin(left_angle);
    params->ray_dir_x1 = cos(right_angle);
    params->ray_dir_y1 = sin(right_angle);
}

static void init_floor_render_params(sfml_t *sfml,
    floor_render_params_t *params)
{
    params->sfml = sfml;
    params->window = sfml->window;
    params->window_size = sfRenderWindow_getSize(sfml->window);
    params->tile_world_size = TILE_SIZE;
    params->block_size = 4;
    params->player = sfml->game->player;
    params->player_height = params->window_size.y / 2 +
        params->player->height_offset;
    params->floor_texture = &sfml->game->floor_texture;
    calculate_ray_directions(params->player, params);
}

static void precalculate_floor_row(floor_render_params_t *params,
    unsigned int y, floor_row_data_t *row_data)
{
    row_data->row_distance = params->player_height /
    (y - params->window_size.y / 2);
    row_data->floor_step_x = row_data->row_distance *
    (params->ray_dir_x1 - params->ray_dir_x0) / params->window_size.x;
    row_data->floor_step_y = row_data->row_distance *
    (params->ray_dir_y1 - params->ray_dir_y0) / params->window_size.x;
    row_data->floor_x_start = params->player->x + row_data->row_distance *
    params->ray_dir_x0;
    row_data->floor_y_start = params->player->y + row_data->row_distance *
    params->ray_dir_y0;
    row_data->brightness = 1.0f / (1.0f + row_data->row_distance * 0.001f);
}

static sfColor calculate_block_color(floor_render_params_t *params,
    float floor_x, float floor_y, floor_row_data_t *row_data)
{
    int cell_x = (int)(floor_x / params->tile_world_size);
    int cell_y = (int)(floor_y / params->tile_world_size);
    float cell_rel_x = fmodf(floor_x / params->tile_world_size, 1.0f);
    float cell_rel_y = fmodf(floor_y / params->tile_world_size, 1.0f);
    int tx;
    int ty;
    sfColor tex_color;
    float final_brightness;

    cell_rel_x += (cell_rel_x < 0) ? 1.0f : 0.0f;
    cell_rel_y += (cell_rel_y < 0) ? 1.0f : 0.0f;
    if (!(cell_x >= 0 && cell_y >= 0))
        return sfColor_fromRGB(0, 0, 50);
    tx = (int)(params->floor_texture->width * cell_rel_x);
    ty = (int)(params->floor_texture->height * cell_rel_y);
    tex_color = sfImage_getPixel(params->floor_texture->image, tx, ty);
    final_brightness = apply_flashlight(params->sfml, floor_x, floor_y,
        row_data->brightness);
    return sfColor_fromRGB(tex_color.r * final_brightness, tex_color.g *
        final_brightness, tex_color.b * final_brightness);
}

static void process_floor_row(floor_render_params_t *par,
    sfRectangleShape *block, unsigned int y, floor_row_data_t *row_data)
{
    float floor_x = row_data->floor_x_start;
    float floor_y = row_data->floor_y_start;
    sfColor color;
    int actual_block_width;
    int actual_block_height;

    for (unsigned int x = 0; x < par->window_size.x; x += par->block_size) {
        color = calculate_block_color(par, floor_x, floor_y, row_data);
        actual_block_width = fmin(par->block_size,
            par->window_size.x - x);
        actual_block_height = fmin(par->block_size,
            par->window_size.y - y);
        sfRectangleShape_setSize(block, (sfVector2f){actual_block_width,
            actual_block_height});
        sfRectangleShape_setPosition(block, (sfVector2f){x, y});
        sfRectangleShape_setFillColor(block, color);
        sfRenderWindow_drawRectangleShape(par->window, block, NULL);
        floor_x += row_data->floor_step_x * par->block_size;
        floor_y += row_data->floor_step_y * par->block_size;
    }
}

void render_textured_floor(sfml_t *sfml)
{
    floor_render_params_t params;
    sfRectangleShape *block = sfRectangleShape_create();
    floor_row_data_t row_data;

    init_floor_render_params(sfml, &params);
    for (unsigned int y = params.window_size.y / 2 + 1; y <
        params.window_size.y; y += params.block_size) {
        precalculate_floor_row(&params, y, &row_data);
        process_floor_row(&params, block, y, &row_data);
    }
    sfRectangleShape_destroy(block);
}

static void render_textured_wall_strip(sfml_t *sfml,
    wall_strip_params_t params)
{
    ray_t *ray = &sfml->game->rays[params.index];
    texture_t *text = &sfml->game->wall_texture;
    float wall_hit_pos = fmodf((ray->was_hit_vertical) ? ray->wall_hit_y :
        ray->wall_hit_x, TILE_SIZE);
    sfRectangleShape *wall_strip = sfRectangleShape_create();
    sfIntRect texture_rect = {.left = (int)(wall_hit_pos * text->width /
    TILE_SIZE) % text->width, .top = 0, .width = 1, .height = text->height};
    float brightness = apply_flashlight(sfml, ray->wall_hit_x, ray->wall_hit_y,
        1.0f / (1.0f + ray->distance * 0.004f));

    sfRectangleShape_setSize(wall_strip, (sfVector2f){params.strip_width + 1,
        params.height});
    sfRectangleShape_setPosition(wall_strip, (sfVector2f){params.index *
        params.strip_width, params.top_pixel});
    sfRectangleShape_setTexture(wall_strip, text->texture, sfFalse);
    sfRectangleShape_setTextureRect(wall_strip, texture_rect);
    sfRectangleShape_setFillColor(wall_strip, sfColor_fromRGB(255 *
        brightness, 255 * brightness, 255 * brightness));
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
            sfml->game->rays[i].distance * cos(sfml->game->rays[i].angle -
            sfml->game->player->angle), window_size.y);
        params.top_pixel = (window_size.y / 2) - (params.height / 2) +
            sfml->game->player->height_offset;
        render_textured_wall_strip(sfml, params);
    }
}

void render_surfaces(sfml_t *sfml)
{
    render_floor_ceiling(sfml);
    render_wall_columns(sfml);
}
