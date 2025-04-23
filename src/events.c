/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** events.c
*/

#include "wolf3d.h"

static int will_collide_with_wall(sfml_t *sfml, float new_x, float new_y)
{
    float padding = 10.0f;
    int map_x;
    int map_y;

    if (new_x < padding || new_x >= MAP_WIDTH * TILE_SIZE - padding ||
        new_y < padding || new_y >= MAP_HEIGHT * TILE_SIZE - padding) {
        return 1;
    }
    map_x = (int)(new_x / TILE_SIZE);
    map_y = (int)(new_y / TILE_SIZE);
    if (sfml->game->map[map_y][map_x] != 0)
        return 1;
    return 0;
}

void events(sfml_t *sfml)
{
    if (sfml->event.type == sfEvtClosed)
        sfRenderWindow_close(sfml->window);
    if (sfml->event.type == sfEvtKeyPressed) {
        if (sfml->event.key.code == sfKeyEscape)
            sfRenderWindow_close(sfml->window);
        if (sfml->event.key.code == sfKeyR)
            reset_map(sfml);
    }
}

void move_player(sfml_t *sfml, float speed, float angle)
{
    float new_x = sfml->game->player->x + cos(angle) * speed;
    float new_y = sfml->game->player->y + sin(angle) * speed;

    if (!will_collide_with_wall(sfml, new_x, sfml->game->player->y))
        sfml->game->player->x = new_x;
    if (!will_collide_with_wall(sfml, sfml->game->player->x, new_y))
        sfml->game->player->y = new_y;
}
