/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** free_particles.c
*/

#include "wolf3d.h"

void free_particle(particle_t *particle)
{
    if (!particle)
        return;
    if (particle->sheet) {
        free_sprite_sheet(particle->sheet);
        particle->sheet = NULL;
    }
    free(particle);
}

void free_particles(sfml_t *sfml)
{
    if (!sfml->game->firesparks)
        return;
    for (int i = 0; i < NUM_PARTICLES; i++)
        free_particle(sfml->game->firesparks[i]);
    free(sfml->game->firesparks);
    sfml->game->firesparks = NULL;
    if (!sfml->game->dusts)
        return;
    for (int i = 0; i < NUM_PARTICLES; i++)
        free_particle(sfml->game->dusts[i]);
    free(sfml->game->dusts);
    sfml->game->dusts = NULL;
}
