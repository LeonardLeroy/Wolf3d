/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** render_floor_ceiling.c
*/

#include "wolf3d.h"

static void destroy_vertex_arrays(sfVertexArray *ceiling_vertices,
    sfVertexArray *floor_vertices)
{
    sfVertexArray_destroy(ceiling_vertices);
    sfVertexArray_destroy(floor_vertices);
}

static void setup_vertex_arrays(sfVertexArray **ceiling, sfVertexArray **floor)
{
    *ceiling = sfVertexArray_create();
    *floor = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(*ceiling, sfTriangles);
    sfVertexArray_setPrimitiveType(*floor, sfTriangles);
}

static void calculate_floor_properties(row_properties_params_t *params,
    vect_t *vect)
{
    float factor1 = powf(params->y / GRID_SIZE_Y, 1.5f);
    float factor2 = powf((params->y + 1) / GRID_SIZE_Y, 1.5f);

    vect->screen_y1_f = params->horizon + factor1 *
        (params->window_height - params->horizon);
    vect->screen_y2_f = params->horizon + factor2 *
        (params->window_height - params->horizon);
    vect->row_distance1_f = params->player_height_times_half /
        params->tan_fov_half / (vect->screen_y1_f - params->horizon);
    vect->row_distance2_f = params->player_height_times_half /
        params->tan_fov_half / (vect->screen_y2_f - params->horizon);
    vect->row_brightness1_f = 1.0f / (1.0f + vect->row_distance1_f * 0.002f);
    vect->row_brightness2_f = 1.0f / (1.0f + vect->row_distance2_f * 0.002f);
}

static void calculate_ceiling_properties(row_properties_params_t *params,
    vect_t *vect)
{
    float factor1 = powf(params->y / GRID_SIZE_Y, 1.5f);
    float factor2 = powf((params->y + 1) / GRID_SIZE_Y, 1.5f);

    vect->screen_y1_c = factor1 * params->horizon;
    vect->screen_y2_c = factor2 * params->horizon;
    vect->row_distance1_c = params->player_height_times_half /
        params->tan_fov_half / (params->horizon - vect->screen_y1_c);
    vect->row_distance2_c = params->player_height_times_half /
        params->tan_fov_half / (params->horizon - vect->screen_y2_c);
    vect->row_brightness1_c = 1.0f / (1.0f + vect->row_distance1_c * 0.002f);
    vect->row_brightness2_c = 1.0f / (1.0f + vect->row_distance2_c * 0.002f);
}

void calculate_row_properties(float y, float horizon,
    float window_height, vect_t *vect)
{
    row_properties_params_t params = {
        .y = y,
        .horizon = horizon,
        .window_height = window_height,
        .tan_fov_half = tanf(FOV / 2.0f),
        .player_height_times_half = PLAYER_HEIGHT * (window_height / 2)
    };

    calculate_floor_properties(&params, vect);
    calculate_ceiling_properties(&params, vect);
}

static void process_grid_cell(int x, sfml_t *sfml, vect_t *vect,
    cos_sin_t cos_sin)
{
    sfVector2u window_size = sfRenderWindow_getSize(sfml->window);

    vect->screen_x1 = (float)x * window_size.x / GRID_SIZE_X;
    vect->screen_x2 = (float)(x + 1) * window_size.x / GRID_SIZE_X;
    vect->ray_dir_x1 = cos_sin.cos.x + (cos_sin.cos.y - cos_sin.cos.x) *
        ((float)x / GRID_SIZE_X);
    vect->ray_dir_y1 = cos_sin.sin.x + (cos_sin.sin.y - cos_sin.sin.x) *
        ((float)x / GRID_SIZE_X);
    vect->ray_dir_x2 = cos_sin.cos.x + (cos_sin.cos.y - cos_sin.cos.x) *
        ((float)(x + 1) / GRID_SIZE_X);
    vect->ray_dir_y2 = cos_sin.sin.x + (cos_sin.sin.y - cos_sin.sin.x) *
        ((float)(x + 1) / GRID_SIZE_X);
}

void render_vertex_arrays(sfml_t *sfml, sfVertexArray *ceiling,
    sfVertexArray *floor)
{
    sfRenderStates ceiling_states = { .blendMode = sfBlendAlpha,
        .transform = sfTransform_Identity,
        .texture = sfml->game->ceiling_texture.texture,
        .shader = NULL};
    sfRenderStates floor_states = { .blendMode = sfBlendAlpha,
        .transform = sfTransform_Identity,
        .texture = sfml->game->floor_texture.texture,
        .shader = NULL};

    sfRenderWindow_drawVertexArray(sfml->window, ceiling, &ceiling_states);
    sfRenderWindow_drawVertexArray(sfml->window, floor, &floor_states);
}

void render_floor_ceiling(sfml_t *sfml)
{
    sfVertexArray *ceiling_vertices;
    sfVertexArray *floor_vertices;
    vect_t vect;
    sfVector2f cos;
    sfVector2f sin;
    sfVector2u window_size = sfRenderWindow_getSize(sfml->window);
    float horizon = window_size.y / 2 + sfml->game->player->height_offset;

    setup_vertex_arrays(&ceiling_vertices, &floor_vertices);
    calculate_camera_vectors(sfml, &cos, &sin);
    for (int y = 0; y < GRID_SIZE_Y; y++) {
        calculate_row_properties(y, horizon, window_size.y, &vect);
        for (int x = 0; x < GRID_SIZE_X; x++) {
            process_grid_cell(x, sfml, &vect, (cos_sin_t){cos, sin});
            draw_vertices(ceiling_vertices, floor_vertices, sfml, &vect);
        }
    }
    render_vertex_arrays(sfml, ceiling_vertices, floor_vertices);
    destroy_vertex_arrays(ceiling_vertices, floor_vertices);
}
