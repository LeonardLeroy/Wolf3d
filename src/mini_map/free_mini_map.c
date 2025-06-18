/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** free_mini_map.c
*/

#include "wolf3d.h"

void free_mini_map(sfml_t *sfml)
{
    mini_map_t *mini_map = sfml->game->mini_map;

    if (!mini_map)
        return;
    if (mini_map->background)
        sfRectangleShape_destroy(mini_map->background);
    if (mini_map->wall_tile)
        sfRectangleShape_destroy(mini_map->wall_tile);
    if (mini_map->player_marker)
        sfSprite_destroy(mini_map->player_marker);
    if (mini_map->player_marker_texture)
        sfTexture_destroy(mini_map->player_marker_texture);
    if (mini_map->title)
        sfText_destroy(mini_map->title);
    free(mini_map);
}
