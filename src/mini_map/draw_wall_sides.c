/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** draw_wall_sides.c
*/

#include "wolf3d.h"

static void draw_top_wall(sfml_t *sfml, sfVector2f position, int x, int y)
{
    sfRectangleShape *line;

    if (y > 0 && sfml->game->map[y - 1][x] == 0) {
        line = sfRectangleShape_create();
        sfRectangleShape_setSize(line, (sfVector2f){TILE_SIZE, 1});
        sfRectangleShape_setPosition(line, position);
        sfRectangleShape_setFillColor(line, sfColor_fromRGB(200, 0, 0));
        sfRenderWindow_drawRectangleShape(sfml->window, line, NULL);
        sfRectangleShape_destroy(line);
    }
}

static void draw_right_wall(sfml_t *sfml, sfVector2f position, int x, int y)
{
    sfRectangleShape *line;

    if (x < MAP_WIDTH - 1 && sfml->game->map[y][x + 1] == 0) {
        line = sfRectangleShape_create();
        sfRectangleShape_setSize(line, (sfVector2f){1, TILE_SIZE});
        sfRectangleShape_setPosition(line,
            (sfVector2f){position.x + TILE_SIZE - 1, position.y});
        sfRectangleShape_setFillColor(line, sfColor_fromRGB(200, 0, 0));
        sfRenderWindow_drawRectangleShape(sfml->window, line, NULL);
        sfRectangleShape_destroy(line);
    }
}

static void draw_bottom_wall(sfml_t *sfml, sfVector2f position, int x, int y)
{
    sfRectangleShape *line;

    if (y < MAP_HEIGHT - 1 && sfml->game->map[y + 1][x] == 0) {
        line = sfRectangleShape_create();
        sfRectangleShape_setSize(line, (sfVector2f){TILE_SIZE, 1});
        sfRectangleShape_setPosition(line,
            (sfVector2f){position.x, position.y + TILE_SIZE - 1});
        sfRectangleShape_setFillColor(line, sfColor_fromRGB(200, 0, 0));
        sfRenderWindow_drawRectangleShape(sfml->window, line, NULL);
        sfRectangleShape_destroy(line);
    }
}

static void draw_left_wall(sfml_t *sfml, sfVector2f position, int x, int y)
{
    sfRectangleShape *line;

    if (x > 0 && sfml->game->map[y][x - 1] == 0) {
        line = sfRectangleShape_create();
        sfRectangleShape_setSize(line, (sfVector2f){1, TILE_SIZE});
        sfRectangleShape_setPosition(line, position);
        sfRectangleShape_setFillColor(line, sfColor_fromRGB(200, 0, 0));
        sfRenderWindow_drawRectangleShape(sfml->window, line, NULL);
        sfRectangleShape_destroy(line);
    }
}

static void draw_edge_walls(sfml_t *sfml, sfVector2f position, int x, int y)
{
    sfRectangleShape *line = sfRectangleShape_create();

    sfRectangleShape_setFillColor(line, sfColor_fromRGB(200, 0, 0));
    if (x == 0 || x == MAP_WIDTH - 1) {
        sfRectangleShape_setSize(line, (sfVector2f){1, TILE_SIZE});
        sfRectangleShape_setPosition(line,
            (sfVector2f){x == 0 ? position.x :
                position.x + TILE_SIZE - 1, position.y});
        sfRenderWindow_drawRectangleShape(sfml->window, line, NULL);
    }
    if (y == 0 || y == MAP_HEIGHT - 1) {
        sfRectangleShape_setSize(line, (sfVector2f){TILE_SIZE, 1});
        sfRectangleShape_setPosition(line,
            (sfVector2f){position.x, y == 0 ?
                position.y : position.y + TILE_SIZE - 1});
        sfRenderWindow_drawRectangleShape(sfml->window, line, NULL);
    }
    sfRectangleShape_destroy(line);
}

void draw_wall_sides(sfml_t *sfml, int x, int y)
{
    sfVector2f position = {x * TILE_SIZE, y * TILE_SIZE};

    draw_top_wall(sfml, position, x, y);
    draw_right_wall(sfml, position, x, y);
    draw_bottom_wall(sfml, position, x, y);
    draw_left_wall(sfml, position, x, y);
    draw_edge_walls(sfml, position, x, y);
}
