/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** init_particles.c
*/

#include "wolf3d.h"

static sprite_sheet_t *create_particle_from_texture(char const *texture)
{
    if (strcmp(texture, "particles/spark") == 0)
        return create_sprite_sheet("particles/spark", 9, 8, 2);
    if (strcmp(texture, "particles/dust") == 0)
        return create_sprite_sheet("particles/dust", 15, 15, 2);
    return NULL;
}

void init_particle(particle_t *particle, char const *texture)
{
    if (!particle)
        return;
    particle->sheet = create_particle_from_texture(texture);
    if (!particle->sheet)
        return;
    particle->life = 0;
    particle->size = 0.0f;
}

void init_particles(sfml_t *sfml)
{
    sfml->game->firesparks = salloc(sizeof(particle_t *) * NUM_PARTICLES);
    for (int i = 0; i < NUM_PARTICLES; i++) {
        sfml->game->firesparks[i] = salloc(sizeof(particle_t));
        init_particle(sfml->game->firesparks[i], "particles/spark");
        if (!sfml->game->firesparks[i]->sheet) {
            free_particles(sfml);
            return;
        }
    }
    sfml->game->dusts = salloc(sizeof(particle_t *) * NUM_PARTICLES);
    for (int i = 0; i < NUM_PARTICLES; i++) {
        sfml->game->dusts[i] = salloc(sizeof(particle_t));
        init_particle(sfml->game->dusts[i], "particles/dust");
        if (!sfml->game->dusts[i]->sheet) {
            free_particles(sfml);
            return;
        }
    }
}
