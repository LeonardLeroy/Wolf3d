/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** draw_enemies.c
*/

#include "wolf3d.h"

static int collect_visible_enemies(sfml_t *sfml,
    enemy_depth_t *visible_enemies)
{
    int visible_count = 0;

    for (int i = 0; i < NUM_ENEMIES; i++) {
        if (sfml->game->enemies[i]->visible) {
            visible_enemies[visible_count].enemy = sfml->game->enemies[i];
            visible_enemies[visible_count].distance =
                sfml->game->enemies[i]->distance;
            visible_count++;
        }
    }
    return visible_count;
}

static void sort_enemies_by_distance(enemy_depth_t *visible_enemies,
    int visible_count, int i)
{
    enemy_depth_t temp;

    for (int j = 0; j < visible_count - i - 1; j++) {
        if (visible_enemies[j].distance < visible_enemies[j + 1].distance) {
            temp = visible_enemies[j];
            visible_enemies[j] = visible_enemies[j + 1];
            visible_enemies[j + 1] = temp;
        }
    }
}

static void render_enemies(sfml_t *sfml, enemy_depth_t *visible_enemies,
    int visible_count)
{
    for (int i = 0; i < visible_count; i++)
        sfRenderWindow_drawSprite(sfml->window,
            visible_enemies[i].enemy->current->sprite, NULL);
}

static void draw_enemies_simple(sfml_t *sfml)
{
    enemy_depth_t visible_enemies[NUM_ENEMIES];
    int visible_count;

    visible_count = collect_visible_enemies(sfml, visible_enemies);
    for (int i = 0; i < visible_count - 1; i++)
        sort_enemies_by_distance(visible_enemies, visible_count, i);
    render_enemies(sfml, visible_enemies, visible_count);
}

void draw_enemies(sfml_t *sfml)
{
    update_visibility_frame(sfml);
    draw_enemies_simple(sfml);
}
