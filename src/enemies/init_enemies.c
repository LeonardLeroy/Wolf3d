/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** init_enemies.c
*/

#include "wolf3d.h"

sfVector2i get_enemy_frame_size(enum ENEMY type)
{
    switch (type) {
        case SHOTGUY:
            return (sfVector2i){64, 60};
        case IMP:
            return (sfVector2i){69, 62};
        default:
            return (sfVector2i){55, 55};
    }
}

static void init_enemy_anims(enemy_t *enemy, char *enemy_name, sfVector2i size)
{
    char *walk_anim_name = my_strcat(enemy_name, "_walk");
    char *shoot_anim_name = my_strcat(enemy_name, "_shoot");
    char *death_anim_name = my_strcat(enemy_name, "_death");
    char *hurt_anim_name = my_strcat(enemy_name, "_hurt");

    enemy->walk = create_sprite_sheet(walk_anim_name, size.x, size.y, 4);
    enemy->shoot = create_sprite_sheet(shoot_anim_name, size.x, size.y, 6);
    enemy->death = create_sprite_sheet(death_anim_name, size.x, size.y, 5);
    enemy->hurt = create_sprite_sheet(hurt_anim_name, size.x, size.y, 2);
    enemy->current = enemy->walk;
    free(walk_anim_name);
    free(shoot_anim_name);
    free(death_anim_name);
    free(hurt_anim_name);
}

static enum ENEMY get_enemy_type(char *enemy_name)
{
    if (strcmp(enemy_name, "enemies/shotguy") == 0)
        return SHOTGUY;
    if (strcmp(enemy_name, "enemies/imp") == 0)
        return IMP;
    return SOLDIER;
}

static int get_enemy_health(enum ENEMY type)
{
    switch (type) {
        case IMP:
            return 50;
        case SHOTGUY:
            return 30;
        default:
            return 20;
    }
}

static char *get_enemy_file(void)
{
    int type = rand() % 3;

    if (type == 1)
        return "enemies/shotguy";
    if (type == 2)
        return "enemies/imp";
    return "enemies/soldier";
}

enemy_t *init_enemy(sfml_t *sfml)
{
    enemy_t *enemy = salloc(sizeof(enemy_t));
    char *enemy_name = get_enemy_file();

    memset(enemy, 0, sizeof(enemy_t));
    find_enemy_position(sfml, enemy);
    enemy->angle = 0.0f;
    enemy->type = get_enemy_type(enemy_name);
    enemy->hp = get_enemy_health(enemy->type);
    init_enemy_anims(enemy, enemy_name, get_enemy_frame_size(enemy->type));
    return enemy;
}

void init_enemies(sfml_t *sfml)
{
    sfml->game->enemies = salloc(sizeof(enemy_t *) * NUM_ENEMIES);
    for (int i = 0; i < NUM_ENEMIES; i++)
        sfml->game->enemies[i] = init_enemy(sfml);
    sfml->game->ai_manager = init_enemy_pathfinding();
}
