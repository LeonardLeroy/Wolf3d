/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-evan.lafolie
** File description:
** procedural_map.c
*/

#include "wolf3d.h"

static void generate_initial_noise(sfml_t *sfml)
{
    for (int y = 1; y < MAP_HEIGHT - 1; y++) {
        for (int x = 1; x < MAP_WIDTH - 1; x++)
            sfml->game->map[y][x] = (rand() % 100 < 45) ? 1 : 0;
    }
}

int count_wall_neighbors(sfml_t *sfml, int x, int y, int radius)
{
    int count = 0;

    for (int dy = -radius; dy <= radius; dy++) {
        for (int dx = -radius; dx <= radius; dx++) {
            count += ((x + dx) < 0 || (x + dx) >= MAP_WIDTH ||
                (y + dy) < 0 || (y + dy) >= MAP_HEIGHT) ? 1 :
                sfml->game->map[(y + dy)][(x + dx)];
        }
    }
    return count;
}

static int get_new_map_value(sfml_t *sfml, int x, int y)
{
    if (x == 0 || x == MAP_WIDTH - 1 || y == 0 || y == MAP_HEIGHT - 1)
        return 1;
    if (count_wall_neighbors(sfml, x, y, 1) >= 5)
        return 1;
    if (count_wall_neighbors(sfml, x, y, 2) <= 2)
        return 0;
    return sfml->game->map[y][x];
}

static void apply_cellular_automata_pass(sfml_t *sfml)
{
    int new_map[MAP_HEIGHT][MAP_WIDTH];

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++)
            new_map[y][x] = get_new_map_value(sfml, x, y);
    }
    memcpy(sfml->game->map, new_map, sizeof(sfml->game->map));
}

static int get_val(int x_or_y, int to_x_or_y)
{
    if (x_or_y < to_x_or_y)
        return x_or_y + 1;
    if (x_or_y > to_x_or_y)
        return x_or_y - 1;
    return x_or_y;
}

void create_tunnel(sfml_t *sfml, point_t from, point_t to)
{
    int x = from.x;
    int y = from.y;
    int val = 0;

    while (x != to.x || y != to.y) {
        sfml->game->map[y][x] = 0;
        if (rand() % 3 == 0) {
            val = sfml->game->map[y][x - 1];
            sfml->game->map[y][x - 1] = (x > 0) ? 0 : val;
            val = sfml->game->map[y - 1][x];
            sfml->game->map[y - 1][x] = (y > 0) ? 0 : val;
        }
        x = get_val(x, to.x);
        y = get_val(y, to.y);
    }
    sfml->game->map[to.y][to.x] = 0;
}

static void add_random_connections(sfml_t *sfml)
{
    int connections = 8 + rand() % 8;
    int x1;
    int y1;
    int x2;
    int y2;

    for (int i = 0; i < connections; i++) {
        x1 = 2 + rand() % (MAP_WIDTH - 4);
        y1 = 2 + rand() % (MAP_HEIGHT - 4);
        x2 = 2 + rand() % (MAP_WIDTH - 4);
        y2 = 2 + rand() % (MAP_HEIGHT - 4);
        if (sfml->game->map[y1][x1] == 0 && sfml->game->map[y2][x2] == 0)
            create_tunnel(sfml, (point_t){x1, y1}, (point_t){x2, y2});
    }
}

static int how_many_exits(sfml_t *sfml, int x, int y)
{
    int exits = 0;

    if (sfml->game->map[y - 1][x] == 0)
        exits++;
    if (sfml->game->map[y + 1][x] == 0)
        exits++;
    if (sfml->game->map[y][x - 1] == 0)
        exits++;
    if (sfml->game->map[y][x + 1] == 0)
        exits++;
    return exits;
}

static void find_valid_spawn(sfml_t *sfml)
{
    int attempts = 0;
    int x;
    int y;

    while (attempts < 100) {
        x = 2 + rand() % (MAP_WIDTH - 4);
        y = 2 + rand() % (MAP_HEIGHT - 4);
        if (sfml->game->map[y][x] == 0 &&
            how_many_exits(sfml, x, y) >= 2) {
            sfml->game->player->x = x * TILE_SIZE + TILE_SIZE / 2;
            sfml->game->player->y = y * TILE_SIZE + TILE_SIZE / 2;
            return;
        }
        attempts++;
    }
    sfml->game->player->x = TILE_SIZE + TILE_SIZE / 2;
    sfml->game->player->y = TILE_SIZE + TILE_SIZE / 2;
    sfml->game->map[1][1] = 0;
}

void generate_procedural_map(sfml_t *sfml)
{
    int region_count;
    region_t **regions;
    int val = 0;

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            val = sfml->game->map[y][x];
            sfml->game->map[y][x] = (x == 0 || x == MAP_WIDTH - 1 || y == 0 ||
                y == MAP_HEIGHT - 1) ? 1 : val;
        }
    }
    generate_initial_noise(sfml);
    for (int i = 0; i < 4; i++)
        apply_cellular_automata_pass(sfml);
    regions = find_all_regions(sfml, &region_count);
    connect_regions(sfml, regions, region_count);
    add_random_connections(sfml);
    adjust_density(sfml);
    find_valid_spawn(sfml);
    free_regions(regions, region_count);
}
