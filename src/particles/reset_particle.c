/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** reset_particles.c
*/

#include "wolf3d.h"

void reset_particle(particle_t *particle)
{
    if (particle->life == 0) {
        particle->life = 0;
        particle->size = 0.0f;
        particle->sheet->anim_timer = 0.0f;
        particle->impact_x = 0.0f;
        particle->impact_y = 0.0f;
        set_current_frame(particle->sheet, 0);
    }
}
