/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** draw_vertices.c
*/

#include "wolf3d.h"

void draw_vertices_floor(sfVertexArray *vertices, sfml_t *sfml, vect_t *vec)
{
    sfVertex v1 = fetch_vect(sfml, (fetch_vect_params_t){vec->ray_dir_x1,
        vec->ray_dir_y1, vec->row_distance1_f, vec->row_brightness1_f,
        vec->screen_x1, vec->screen_y1_f});
    sfVertex v2 = fetch_vect(sfml, (fetch_vect_params_t){vec->ray_dir_x2,
        vec->ray_dir_y2, vec->row_distance1_f, vec->row_brightness1_f,
        vec->screen_x2, vec->screen_y1_f});
    sfVertex v3 = fetch_vect(sfml, (fetch_vect_params_t){vec->ray_dir_x1,
        vec->ray_dir_y1, vec->row_distance2_f, vec->row_brightness2_f,
        vec->screen_x1, vec->screen_y2_f});
    sfVertex v4 = fetch_vect(sfml, (fetch_vect_params_t){vec->ray_dir_x2,
        vec->ray_dir_y2, vec->row_distance2_f, vec->row_brightness2_f,
        vec->screen_x2, vec->screen_y2_f});

    sfVertexArray_append(vertices, v1);
    sfVertexArray_append(vertices, v2);
    sfVertexArray_append(vertices, v3);
    sfVertexArray_append(vertices, v2);
    sfVertexArray_append(vertices, v4);
    sfVertexArray_append(vertices, v3);
}

void draw_vertices_ceiling(sfVertexArray *vertices, sfml_t *sfml, vect_t *vec)
{
    sfVertex v1 = fetch_vect(sfml, (fetch_vect_params_t){vec->ray_dir_x1,
        vec->ray_dir_y1, vec->row_distance1_c, vec->row_brightness1_c,
        vec->screen_x1, vec->screen_y1_c});
    sfVertex v2 = fetch_vect(sfml, (fetch_vect_params_t){vec->ray_dir_x2,
        vec->ray_dir_y2, vec->row_distance1_c, vec->row_brightness1_c,
        vec->screen_x2, vec->screen_y1_c});
    sfVertex v3 = fetch_vect(sfml, (fetch_vect_params_t){vec->ray_dir_x1,
        vec->ray_dir_y1, vec->row_distance2_c, vec->row_brightness2_c,
        vec->screen_x1, vec->screen_y2_c});
    sfVertex v4 = fetch_vect(sfml, (fetch_vect_params_t){vec->ray_dir_x2,
        vec->ray_dir_y2, vec->row_distance2_c, vec->row_brightness2_c,
        vec->screen_x2, vec->screen_y2_c});

    sfVertexArray_append(vertices, v1);
    sfVertexArray_append(vertices, v2);
    sfVertexArray_append(vertices, v3);
    sfVertexArray_append(vertices, v2);
    sfVertexArray_append(vertices, v4);
    sfVertexArray_append(vertices, v3);
}

void draw_vertices(sfVertexArray *ceiling_vertices,
    sfVertexArray *floor_vertices, sfml_t *sfml, vect_t *vec)
{
    draw_vertices_floor(floor_vertices, sfml, vec);
    draw_vertices_ceiling(ceiling_vertices, sfml, vec);
}
