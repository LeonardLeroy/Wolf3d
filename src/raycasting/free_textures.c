/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** free_textures.c
*/

#include "wolf3d.h"

static void free_wall_texture(sfml_t *sfml)
{
    sfTexture_destroy(sfml->game->wall_texture.texture);
    sfml->game->wall_texture.texture = NULL;
    sfImage_destroy(sfml->game->wall_texture.image);
    sfml->game->wall_texture.image = NULL;
}

static void free_floor_texture(sfml_t *sfml)
{
    sfTexture_destroy(sfml->game->floor_texture.texture);
    sfml->game->floor_texture.texture = NULL;
    sfImage_destroy(sfml->game->floor_texture.image);
    sfml->game->floor_texture.image = NULL;
}

static void free_ceiling_texture(sfml_t *sfml)
{
    sfTexture_destroy(sfml->game->ceiling_texture.texture);
    sfml->game->ceiling_texture.texture = NULL;
    sfImage_destroy(sfml->game->ceiling_texture.image);
    sfml->game->ceiling_texture.image = NULL;
}

void free_textures(sfml_t *sfml)
{
    free_wall_texture(sfml);
    free_floor_texture(sfml);
    free_ceiling_texture(sfml);
}
