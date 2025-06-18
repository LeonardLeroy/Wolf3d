/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** update_particles.c
*/

#include "wolf3d.h"

void update_particle(sfml_t *sfml, particle_t *particle)
{
    particle->sheet->anim_timer += sfml->clocks->deltaTime;
    if (particle->life > 0)
        update_particle_position(sfml, particle);
    if (particle->sheet->anim_timer >= FRAME_DURATION) {
        particle->sheet->anim_timer -= FRAME_DURATION;
        particle->life -= 1;
        sfSprite_move(particle->sheet->sprite, (sfVector2f)
            {0.0f, -(particle->size / 4.0f)});
    }
    if (particle->life == 2)
        set_current_frame(particle->sheet, 1);
}

void update_particles(sfml_t *sfml)
{
    for (int i = 0; i < NUM_PARTICLES; i++) {
        if (sfml->game->dusts[i]->life > 0) {
            update_particle(sfml, sfml->game->dusts[i]);
            reset_particle(sfml->game->dusts[i]);
        }
    }
    for (int i = 0; i < NUM_PARTICLES; i++) {
        if (sfml->game->firesparks[i]->life > 0) {
            update_particle(sfml, sfml->game->firesparks[i]);
            reset_particle(sfml->game->firesparks[i]);
        }
    }
}

void draw_particles(sfml_t *sfml)
{
    for (int i = 0; i < NUM_PARTICLES; i++) {
        if (sfml->game->dusts[i]->life > 0) {
            sfRenderWindow_drawSprite(sfml->window,
                sfml->game->dusts[i]->sheet->sprite, NULL);
        }
    }
    for (int i = 0; i < NUM_PARTICLES; i++) {
        if (sfml->game->firesparks[i]->life > 0) {
            sfRenderWindow_drawSprite(sfml->window,
                sfml->game->firesparks[i]->sheet->sprite, NULL);
        }
    }
}
