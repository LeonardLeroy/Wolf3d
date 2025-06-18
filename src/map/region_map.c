/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-evan.lafolie
** File description:
** region_map.c
*/

#include "wolf3d.h"

region_t *create_region(void)
{
    region_t *region = salloc(sizeof(region_t));

    region->capacity = 100;
    region->size = 0;
    region->points = salloc(sizeof(point_t) * region->capacity);
    return region;
}

void free_regions(region_t **regions, int region_count)
{
    for (int i = 0; i < region_count; i++) {
        if (regions[i]) {
            free(regions[i]->points);
            free(regions[i]);
        }
    }
    free(regions);
}

void add_point_to_region(region_t *region, int x, int y)
{
    if (region->size >= region->capacity) {
        region->capacity *= 2;
        region->points = realloc(region->points, sizeof(point_t) *
        region->capacity);
    }
    region->points[region->size].x = x;
    region->points[region->size].y = y;
    region->size++;
}

static void create_basics_connections(sfml_t *sfml, region_t **regions,
    int region_count)
{
    point_t from;
    point_t to;

    for (int i = 0; i < region_count - 1; i++) {
        from = regions[i]->points[rand() % regions[i]->size];
        to = regions[i + 1]->points[rand() % regions[i + 1]->size];
        create_tunnel(sfml, from, to);
    }
}

void connect_regions(sfml_t *sfml, region_t **regions, int region_count)
{
    int extra_connections = region_count / 2 + rand() % 3;
    point_t from;
    point_t to;
    int r1;
    int r2;

    if (region_count < 2)
        return;
    create_basics_connections(sfml, regions, region_count);
    for (int i = 0; i < extra_connections; i++) {
        r1 = rand() % region_count;
        r2 = rand() % region_count;
        if (r1 != r2) {
            from = regions[r1]->points[rand() % regions[r1]->size];
            to = regions[r2]->points[rand() % regions[r2]->size];
            create_tunnel(sfml, from, to);
        }
    }
}
