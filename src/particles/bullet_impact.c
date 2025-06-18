/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** bullet_impact.c
*/

#include "wolf3d.h"

static float impact_offset_from_id(enum WEAPONS type, int id)
{
    if (type == SHOTGUN)
        return -30 + (10 * id);
    if (type == SUPER_SHOTGUN)
        return (rand() % 100) - 50;
    return 0;
}

int is_enemy_hit(enemy_t *enemy, float current_x, float current_y)
{
    float dx = current_x - enemy->x;
    float dy = current_y - enemy->y;
    float distance = sqrt(dx * dx + dy * dy);
    float hit_range = enemy->scale * 2.0f;

    return distance < hit_range;
}

static int check_for_enemies(sfml_t *sfml, float current_x, float current_y)
{
    for (int i = 0; i < NUM_ENEMIES; i++) {
        if (sfml->game->enemies[i]->hp <= 0)
            continue;
        if (is_enemy_hit(sfml->game->enemies[i], current_x, current_y)) {
            hurt_enemy(sfml, sfml->game->enemies[i]);
            return 1;
        }
    }
    return 0;
}

static int check_for_walls(sfml_t *sfml, bullet_impact_t *impact,
    wall_check_args_t args)
{
    if (is_wall(sfml, args.current_x, args.current_y)) {
        impact->hit_x = args.current_x - args.dx;
        impact->hit_y = args.current_y - args.dy;
        impact->distance = calculate_actual_distance(sfml->game->player->x,
            sfml->game->player->y, impact->hit_x, impact->hit_y);
        impact->hit_found = 1;
        return 1;
    }
    return 0;
}

bullet_impact_t calculate_bullet_impact(sfml_t *sfml, int id)
{
    bullet_impact_t impact = {0};
    player_t *player = sfml->game->player;
    float impact_offset = impact_offset_from_id(player->weapon->type, id);
    float current_x = player->x + impact_offset;
    float current_y = player->y + impact_offset;
    float dx = cos(player->angle);
    float dy = sin(player->angle);

    for (; is_within_bounds(current_x, current_y); current_x += dx) {
        if (check_for_enemies(sfml, current_x, current_y))
            return impact;
        if (check_for_walls(sfml, &impact, (wall_check_args_t)
            {current_x, current_y, dx, dy}))
            return impact;
        current_y += dy;
    }
    return impact;
}

static float calculate_particle_size_from_distance(float distance)
{
    float base_size = 8.0f;
    float size = base_size * (200.0f / (distance + 50.0f));

    return size;
}

void play_particle_at_impact(sfml_t *sfml, particle_t *particle,
    bullet_impact_t impact)
{
    if (!impact.hit_found || !particle || particle->life != 0)
        return;
    particle->life = 4;
    particle->size = calculate_particle_size_from_distance(impact.distance);
    particle->impact_x = impact.hit_x;
    particle->impact_y = impact.hit_y;
    sfSprite_setScale(particle->sheet->sprite, (sfVector2f)
        {particle->size, particle->size});
    if (particle->life > 0)
        update_particle_position(sfml, particle);
}

void set_particle_position(sfml_t *sfml, particle_t *particle,
    float screen_x, float screen_y)
{
    sfFloatRect bounds = sfSprite_getLocalBounds(particle->sheet->sprite);
    float brightness = 1.0f / (1.0f + particle->distance * (2 / 5000.0f));

    sfSprite_setOrigin(particle->sheet->sprite, (sfVector2f){
        bounds.width / 2.0f,
        bounds.height / 2.0f
    });
    sfSprite_setColor(particle->sheet->sprite, sfColor_fromRGB(255 *
        brightness, 255 * brightness, 255 * brightness));
    particle->size = calculate_particle_size_from_distance(particle->distance);
    sfSprite_setScale(particle->sheet->sprite, (sfVector2f)
        {particle->size, particle->size});
    sfSprite_setPosition(particle->sheet->sprite, (sfVector2f)
        {screen_x, screen_y + sfml->game->player->height_offset});
}

void update_particle_position(sfml_t *sfml, particle_t *particle)
{
    player_t *player = sfml->game->player;
    sfVector2u window_size = sfRenderWindow_getSize(sfml->window);
    float dx = particle->impact_x - player->x;
    float dy = particle->impact_y - player->y;
    float distance = sqrt(dx * dx + dy * dy);
    float relative_angle = normalize_angle(atan2(dy, dx) - player->angle);
    float distance_proj_plane = (window_size.x / 2.0f) / tan(FOV / 2.0f);
    float screen_x = (window_size.x / 2.0f) +
        (tan(relative_angle) * distance_proj_plane);
    float screen_y = (window_size.y / 2.0f) +
        (distance_proj_plane / distance);

    particle->distance = distance;
    set_particle_position(sfml, particle, screen_x, screen_y);
}
