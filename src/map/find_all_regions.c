/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-evan.lafolie
** File description:
** find_all_regions.c
*/

#include "wolf3d.h"
#include <stdbool.h>

static int get_stack_size(point_t *stack, int x, int y, int stack_size)
{
    stack[stack_size] = (point_t){x + 1, y};
    stack_size++;
    stack[stack_size] = (point_t){x - 1, y};
    stack_size++;
    stack[stack_size] = (point_t){x, y + 1};
    stack_size++;
    stack[stack_size] = (point_t){x, y - 1};
    stack_size++;
    return stack_size;
}

static bool is_valid_start_point(sfml_t *sfml, int x, int y,
    int visited[MAP_HEIGHT][MAP_WIDTH])
{
    return !visited[y][x] && sfml->game->map[y][x] != 1;
}

static bool is_valid_point(sfml_t *sfml, int x, int y,
    int visited[MAP_HEIGHT][MAP_WIDTH])
{
    return (x >= 1 && x < MAP_WIDTH - 1 && y >= 1 && y < MAP_HEIGHT - 1 &&
        !visited[y][x] && sfml->game->map[y][x] != 1);
}

static void process_flood_fill_point(region_t *region, point_t point,
    int visited[MAP_HEIGHT][MAP_WIDTH])
{
    visited[point.y][point.x] = 1;
    add_point_to_region(region, point.x, point.y);
}

static point_t *initialize_flood_fill_stack(int start_x, int start_y,
    int *stack_size)
{
    point_t *stack = salloc(sizeof(point_t) * MAP_WIDTH * MAP_HEIGHT);

    stack[0] = (point_t){start_x, start_y};
    *stack_size = 1;
    return stack;
}

static void execute_flood_fill(flood_fill_context_t *ctx, region_t *region)
{
    point_t current;

    while (*ctx->stack_size > 0) {
        (*ctx->stack_size)--;
        current = ctx->stack[*ctx->stack_size];
        if (!is_valid_point(ctx->sfml, current.x, current.y, ctx->visited))
            continue;
        process_flood_fill_point(region, current, ctx->visited);
        *ctx->stack_size = get_stack_size(ctx->stack, current.x, current.y,
            *ctx->stack_size);
    }
}

static region_t *flood_fill_region(flood_fill_context_t *ctx,
    int start_x, int start_y)
{
    region_t *region;

    if (!is_valid_start_point(ctx->sfml, start_x, start_y, ctx->visited))
        return NULL;
    region = create_region();
    ctx->stack = initialize_flood_fill_stack(start_x, start_y,
        ctx->stack_size);
    execute_flood_fill(ctx, region);
    free(ctx->stack);
    return region;
}

static void process_position(flood_fill_context_t *ctx, int x, int y)
{
    region_t *region;

    if (!ctx->visited[y][x] && ctx->sfml->game->map[y][x] == 0) {
        region = flood_fill_region(ctx, x, y);
        if (region && region->size > 5) {
            ctx->regions[*ctx->region_count] = region;
            (*ctx->region_count)++;
            return;
        }
        if (region) {
            free(region->points);
            free(region);
        }
    }
}

region_t **find_all_regions(sfml_t *sfml, int *region_count)
{
    flood_fill_context_t ctx = {0};
    int stack_size = 0;

    ctx.sfml = sfml;
    ctx.regions = salloc(sizeof(region_t *) * 50);
    ctx.region_count = region_count;
    ctx.stack_size = &stack_size;
    *region_count = 0;
    for (int y = 1; y < MAP_HEIGHT - 1; y++) {
        for (int x = 1; x < MAP_WIDTH - 1; x++)
            process_position(&ctx, x, y);
    }
    return ctx.regions;
}
