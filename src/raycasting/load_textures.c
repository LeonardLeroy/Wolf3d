/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** load_textures.c
*/

#include "wolf3d.h"

static void load_wall_texture(sfml_t *sfml, char const *texture)
{
    sfml->game->wall_texture.texture = sfTexture_createFromFile(
        image(texture), NULL
    );
    sfml->game->wall_texture.image = sfTexture_copyToImage(
        sfml->game->wall_texture.texture
    );
    sfml->game->wall_texture.width = sfImage_getSize(
        sfml->game->wall_texture.image
    ).x;
    sfml->game->wall_texture.height = sfImage_getSize(
        sfml->game->wall_texture.image
    ).y;
}

static void load_floor_texture(sfml_t *sfml, char const *texture)
{
    sfml->game->floor_texture.texture = sfTexture_createFromFile(
        image(texture), NULL
    );
    sfml->game->floor_texture.image = sfTexture_copyToImage(
        sfml->game->floor_texture.texture
    );
    sfml->game->floor_texture.width = sfImage_getSize(
        sfml->game->floor_texture.image
    ).x;
    sfml->game->floor_texture.height = sfImage_getSize(
        sfml->game->floor_texture.image
    ).y;
}

static void load_ceiling_texture(sfml_t *sfml, char const *texture)
{
    sfml->game->ceiling_texture.texture = sfTexture_createFromFile(
        image(texture), NULL
    );
    sfml->game->ceiling_texture.image = sfTexture_copyToImage(
        sfml->game->ceiling_texture.texture
    );
    sfml->game->ceiling_texture.width = sfImage_getSize(
        sfml->game->ceiling_texture.image
    ).x;
    sfml->game->ceiling_texture.height = sfImage_getSize(
        sfml->game->ceiling_texture.image
    ).y;
}

void load_textures(sfml_t *sfml)
{
    load_wall_texture(sfml, WALL_TEXTURE);
    load_floor_texture(sfml, FLOOR_TEXTURE);
    load_ceiling_texture(sfml, CEILING_TEXTURE);
}
