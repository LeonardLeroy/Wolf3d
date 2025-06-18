/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** init_game.c
*/

#include "wolf3d.h"

precise_visibility_manager_t *init_precise_visibility_manager(void)
{
    precise_visibility_manager_t *manager =
        malloc(sizeof(precise_visibility_manager_t));

    if (!manager)
        return NULL;
    for (int i = 0; i < NUM_ENEMIES; i++) {
        manager->visibility_cache[i].frame_calculated = -1;
        manager->visibility_cache[i].cached_visibility.visibility_mask = NULL;
        manager->visibility_cache[i].last_player_x = 0.0f;
        manager->visibility_cache[i].last_player_y = 0.0f;
        manager->visibility_cache[i].last_player_angle = 0.0f;
        manager->visibility_cache[i].last_enemy_x = 0.0f;
        manager->visibility_cache[i].last_enemy_y = 0.0f;
    }
    manager->current_visibility_frame = 0;
    return manager;
}

void init_visibility_context(visibility_context_t *ctx)
{
    for (int i = 0; i < NUM_ENEMIES; i++) {
        ctx->cache[i].frame_calculated = -1;
        ctx->cache[i].player_x = 0.0f;
        ctx->cache[i].player_y = 0.0f;
        ctx->cache[i].player_angle = 0.0f;
        ctx->cache[i].enemy_x = 0.0f;
        ctx->cache[i].enemy_y = 0.0f;
    }
    ctx->current_frame = 0;
}

static void init_game_2(sfml_t *sfml)
{
    sfml->game->visibility_manager = init_precise_visibility_manager();
    if (!sfml->game->visibility_manager) {
        free(sfml->game);
        sfml->game = NULL;
        return;
    }
}

void init_game(sfml_t *sfml)
{
    sfml->game = salloc(sizeof(game_t));
    sfml->game->game_substate = NORMAL;
    init_game_2(sfml);
    init_visibility_context(&sfml->game->visibility_ctx);
    init_player(sfml);
    init_hud(sfml);
    init_cameras(sfml);
    init_weapons(sfml);
    init_mini_map(sfml);
    load_textures(sfml);
    open_map(sfml, NULL);
    init_enemies(sfml);
    init_sprites(sfml);
    init_particles(sfml);
    sfml->game->rays = salloc(sizeof(ray_t) * NUM_RAYS);
    for (int i = 0; i < NUM_RAYS; i++)
        init_rays(&sfml->game->rays[i]);
}
