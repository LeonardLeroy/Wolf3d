/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** draw_mini_map.c
*/

#include "wolf3d.h"

static void draw_mini_map_wall_check(sfml_t *sfml, int x, int y)
{
    if (sfml->game->map[y][x] != 0)
        draw_wall_sides(sfml, x, y);
}

static void draw_mini_map_walls(sfml_t *sfml)
{
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++)
            draw_mini_map_wall_check(sfml, x, y);
    }
}

static void draw_mini_map_player(sfml_t *sfml)
{
    mini_map_t *mini_map = sfml->game->mini_map;
    player_t *player = sfml->game->player;
    sfFloatRect bounds;

    bounds = sfSprite_getLocalBounds(mini_map->player_marker);
    sfSprite_setOrigin(mini_map->player_marker,
        (sfVector2f){bounds.width / 2, bounds.height / 2});
    sfSprite_setPosition(mini_map->player_marker,
        (sfVector2f){player->x, player->y});
    sfSprite_setRotation(mini_map->player_marker,
        (player->angle * 180 / PI) + 90);
    sfRenderWindow_drawSprite(sfml->window,
        mini_map->player_marker, NULL);
}

static void update_mini_map_camera(sfml_t *sfml)
{
    player_t *player = sfml->game->player;
    sfView *view = sfml->game->cameras->camGame;

    sfView_setCenter(view, (sfVector2f){player->x, player->y});
}

static void draw_mini_map_text(sfml_t *sfml)
{
    mini_map_t *mini_map = sfml->game->mini_map;

    sfRenderWindow_drawText(sfml->window, mini_map->title, NULL);
}

void render_mini_map(sfml_t *sfml)
{
    mini_map_t *mini_map = sfml->game->mini_map;

    update_mini_map_camera(sfml);
    sfRenderWindow_drawRectangleShape(sfml->window,
        mini_map->background, NULL);
    draw_mini_map_walls(sfml);
    draw_mini_map_player(sfml);
    sfRenderWindow_setView(sfml->window, sfml->game->cameras->camHUD);
    draw_mini_map_text(sfml);
}
