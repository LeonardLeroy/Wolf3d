/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** free_game.c
*/

#include "wolf3d.h"

void free_game_2(sfml_t *sfml)
{
    if (sfml->game && sfml->game->visibility_manager) {
        cleanup_precise_visibility_cache(sfml->game->visibility_manager);
        sfml->game->visibility_manager = NULL;
    }
}

void free_game(sfml_t *sfml)
{
    free_game_2(sfml);
    free_cameras(sfml);
    free_player(sfml);
    free_enemies(sfml);
    free_hud(sfml);
    free_mini_map(sfml);
    free_textures(sfml);
    free_particles(sfml);
    free_sprites(sfml);
    if (sfml->game->ai_manager) {
        cleanup_enemy_pathfinding(sfml->game->ai_manager);
        sfml->game->ai_manager = NULL;
    }
    for (int i = 0; i < NUM_RAYS; i++)
        init_rays(&sfml->game->rays[i]);
    free(sfml->game->rays);
    sfml->game->rays = NULL;
    free(sfml->game);
    sfml->game = NULL;
}
