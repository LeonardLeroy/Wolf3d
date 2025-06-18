/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** init_mini_map.c
*/

#include "wolf3d.h"

static void init_mini_map_background(mini_map_t *mini_map)
{
    mini_map->background = sfRectangleShape_create();
    sfRectangleShape_setSize(mini_map->background,
        (sfVector2f){MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE});
    sfRectangleShape_setFillColor(mini_map->background,
        sfColor_fromRGB(0, 0, 0));
    sfRectangleShape_setPosition(mini_map->background,
        (sfVector2f){0, 0});
}

static void init_mini_map_wall(mini_map_t *mini_map)
{
    mini_map->wall_tile = sfRectangleShape_create();
    sfRectangleShape_setSize(mini_map->wall_tile,
        (sfVector2f){TILE_SIZE, TILE_SIZE});
    sfRectangleShape_setOutlineColor(mini_map->wall_tile,
        sfColor_fromRGB(200, 0, 0));
    sfRectangleShape_setOutlineThickness(mini_map->wall_tile, 1);
    sfRectangleShape_setFillColor(mini_map->wall_tile, sfTransparent);
}

static void init_mini_map_player(mini_map_t *mini_map)
{
    sfFloatRect bounds;

    mini_map->player_marker_texture = sfTexture_createFromFile(
        image("arrow"), NULL);
    mini_map->player_marker = sfSprite_create();
    sfSprite_setTexture(mini_map->player_marker,
        mini_map->player_marker_texture, sfTrue);
    sfSprite_setScale(mini_map->player_marker,
        (sfVector2f){0.5, 0.5});
    bounds = sfSprite_getLocalBounds(mini_map->player_marker);
    sfSprite_setOrigin(mini_map->player_marker,
        (sfVector2f){bounds.width / 2, bounds.height / 2});
}

static void init_mini_map_text(sfml_t *sfml, mini_map_t *mini_map)
{
    mini_map->title = sfText_create();
    sfText_setString(mini_map->title, "MINI MAP");
    sfText_setFont(mini_map->title, sfml->fonts->eternal_ui);
    sfText_setCharacterSize(mini_map->title, 32);
    sfText_setPosition(mini_map->title, (sfVector2f){10, 0});
}

void init_mini_map(sfml_t *sfml)
{
    mini_map_t *mini_map = salloc(sizeof(mini_map_t));

    init_mini_map_background(mini_map);
    init_mini_map_wall(mini_map);
    init_mini_map_player(mini_map);
    init_mini_map_text(sfml, mini_map);
    sfml->game->mini_map = mini_map;
}
