/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-evan.lafolie
** File description:
** render_utils.c
*/

#include "wolf3d.h"

void calculate_camera_vectors(sfml_t *sfml, sfVector2f *cos,
    sfVector2f *sin)
{
    cos->x = cosf(sfml->game->player->angle - FOV / 2.0f);
    sin->x = sinf(sfml->game->player->angle - FOV / 2.0f);
    cos->y = cosf(sfml->game->player->angle + FOV / 2.0f);
    sin->y = sinf(sfml->game->player->angle + FOV / 2.0f);
}

void calculate_ray_angle(triangle_params_t *params, unsigned int x,
    sfVector2u window_size, float player_angle)
{
    params->ray_angle = player_angle - FOV / 2 + (x / (float)window_size.x)
    * FOV;
    params->next_ray_angle = player_angle - FOV / 2 + ((x + 1) /
    (float)window_size.x) * FOV;
    params->x = x;
}

sfVertexArray *create_vertex_array(void)
{
    sfVertexArray *vertices = sfVertexArray_create();

    sfVertexArray_setPrimitiveType(vertices, sfTriangles);
    return vertices;
}

static sfColor fetch_color(float brightness)
{
    unsigned int value = 255 * brightness;

    if (value > 255)
        value = 255;
    return sfColor_fromRGB(value, value, value);
}

sfVertex fetch_vect(sfml_t *sfml, fetch_vect_params_t params)
{
    sfVector2f tex = {
        fmodf(sfml->game->player->x / 1.5 + params.ray_dir_x * params.row_dist,
            TILE_SIZE) / TILE_SIZE * TILE_SIZE,
        fmodf(sfml->game->player->y / 1.5 + params.ray_dir_y * params.row_dist,
            TILE_SIZE) / TILE_SIZE * TILE_SIZE
    };
    float brightness;

    if (tex.x < 0)
        tex.x += TILE_SIZE;
    if (tex.y < 0)
        tex.y += TILE_SIZE;
    brightness = apply_flashlight(sfml, sfml->game->player->x +
        params.ray_dir_x * params.row_dist, sfml->game->player->y +
        params.ray_dir_y * params.row_dist, params.row_brightness);
    return (sfVertex){.position = {params.screen_x, params.screen_y},
        .color = fetch_color(brightness), .texCoords = {tex.x, tex.y}};
}

static sfVector2f fetch_tex(float ray_angle, float row_distance, sfml_t *sfml,
    int is_floor)
{
    texture_t *texture = (is_floor) ? &sfml->game->floor_texture :
    &sfml->game->ceiling_texture;
    float world_x = sfml->game->player->x + cos(ray_angle) * row_distance;
    float world_y = sfml->game->player->y + sin(ray_angle) * row_distance;
    sfVector2f tex = {
        fmodf(world_x, TILE_SIZE) * texture->width / TILE_SIZE,
        fmodf(world_y, TILE_SIZE) * texture->height / TILE_SIZE
    };

    tex.x = fmodf(tex.x, texture->width);
    tex.y = fmodf(tex.y, texture->height);
    return tex;
}

void add_triangle(triangle_params_t par, sfml_t *sfml)
{
    sfVector2f tex1 = fetch_tex(par.ray_angle, par.row_distance, sfml, 1);
    sfVector2f tex2 = fetch_tex(par.next_ray_angle, par.row_distance, sfml, 1);
    sfVector2f tex3 = fetch_tex(par.ray_angle, par.next_row_distance, sfml, 1);
    sfVector2f tex4 = fetch_tex(par.next_ray_angle, par.next_row_distance,
        sfml, 1);
    sfVertex v1 = {.position = {par.x, par.y}, .color =
    fetch_color(par.brightness), .texCoords = {tex1.x, tex1.y}};
    sfVertex v2 = {.position = {par.x + 1, par.y}, .color =
    fetch_color(par.brightness), .texCoords = {tex2.x, tex2.y}};
    sfVertex v3 = {.position = {par.x, par.y + 1}, .color =
    fetch_color(par.next_brightness), .texCoords = {tex3.x, tex3.y}};
    sfVertex v4 = {.position = {par.x + 1, par.y + 1}, .color =
    fetch_color(par.next_brightness), .texCoords = {tex4.x, tex4.y}};

    sfVertexArray_append(par.vertices, v1);
    sfVertexArray_append(par.vertices, v2);
    sfVertexArray_append(par.vertices, v3);
    sfVertexArray_append(par.vertices, v2);
    sfVertexArray_append(par.vertices, v4);
    sfVertexArray_append(par.vertices, v3);
}
