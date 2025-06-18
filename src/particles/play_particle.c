/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** play_particle.c
*/

#include "wolf3d.h"

void play_particle(sfml_t *sfml, particle_t *particle)
{
    particle->life = 4;
    particle->size = 7 + rand() % 2 - 0.5f;
    sfSprite_setScale(particle->sheet->sprite, (sfVector2f)
        {particle->size, particle->size});
    sfSprite_setPosition(particle->sheet->sprite, (sfVector2f){
        get_centered_x(sfml, particle->sheet->sprite),
        get_centered_y(sfml, particle->sheet->sprite) * particle->size
    });
}

void play_fire_particles(sfml_t *sfml, bullet_impact_t impact)
{
    weapon_t *weapon = sfml->game->player->weapon;

    if (weapon->type == FIST)
        return;
    for (int i = 0; i < NUM_PARTICLES; i++) {
        if (sfml->game->dusts[i]->life == 0) {
            play_particle_at_impact(sfml, sfml->game->firesparks[i], impact);
            break;
        }
    }
}

void play_dust_particles(sfml_t *sfml, bullet_impact_t impact)
{
    if (sfml->game->player->weapon->type == FIST && impact.distance > 40)
        return;
    for (int i = 0; i < NUM_PARTICLES; i++) {
        if (sfml->game->dusts[i]->life == 0) {
            play_particle_at_impact(sfml, sfml->game->dusts[i], impact);
            break;
        }
    }
}

void play_weapon_particle(sfml_t *sfml, int id)
{
    bullet_impact_t impact = calculate_bullet_impact(sfml, id);

    if (!impact.hit_found)
        return;
    play_fire_particles(sfml, impact);
    play_dust_particles(sfml, impact);
}
