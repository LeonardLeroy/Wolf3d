/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** reset_game.c
*/

#include "wolf3d.h"

static void frees_game(sfml_t *sfml)
{
    free_cameras(sfml);
    free_player(sfml);
    free_enemies(sfml);
    free_hud(sfml);
    if (sfml->game->ai_manager)
        cleanup_enemy_pathfinding(sfml->game->ai_manager);
    if (sfml->game->visibility_manager) {
        cleanup_precise_visibility_cache(sfml->game->visibility_manager);
        sfml->game->visibility_manager = init_precise_visibility_manager();
    }
}

void reset_game(sfml_t *sfml)
{
    frees_game(sfml);
    for (int i = 0; i < NUM_RAYS; i++)
        init_rays(&sfml->game->rays[i]);
    free(sfml->game->rays);
    sfml->game->rays = NULL;
    init_player(sfml);
    init_hud(sfml);
    init_cameras(sfml);
    init_enemies(sfml);
    sfml->game->ai_manager = init_enemy_pathfinding();
    sfml->game->player->weapon =
        (sfml->game->weapons) ? sfml->game->weapons[PISTOL] : NULL;
    set_current_frame(sfml->game->player->weapon->sheet, 0);
    sfml->game->rays = salloc(sizeof(ray_t) * NUM_RAYS);
    for (int i = 0; i < NUM_RAYS; i++)
        init_rays(&sfml->game->rays[i]);
    init_map(sfml, NULL);
    sfml->menu->game_started = 0;
}
