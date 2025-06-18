/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-evan.lafolie
** File description:
** enemy_sprites.c
*/

#include "wolf3d.h"

static enemy_params_t get_enemy_params(int enemy_type)
{
    enemy_params_t params;

    switch (enemy_type) {
        case SHOTGUY:
            params.frame_size = (sfVector2i){64, 60};
            params.name = "enemies/shotguy";
            break;
        case IMP:
            params.frame_size = (sfVector2i){69, 62};
            params.name = "enemies/imp";
            break;
        default:
            params.frame_size = (sfVector2i){55, 55};
            params.name = "enemies/soldier";
            break;
    }
    return params;
}

static void create_enemy_sprite_sheets(enemy_t *enemy, const char *base_name,
    sfVector2i frame_size)
{
    char *walk_name = my_strcat(base_name, "_walk");
    char *shoot_name = my_strcat(base_name, "_shoot");
    char *death_name = my_strcat(base_name, "_death");
    char *hurt_name = my_strcat(base_name, "_hurt");

    enemy->walk = create_sprite_sheet(walk_name, frame_size.x, frame_size.y,
        4);
    enemy->shoot = create_sprite_sheet(shoot_name, frame_size.x, frame_size.y,
        2);
    enemy->death = create_sprite_sheet(death_name, frame_size.x, frame_size.y,
        5);
    enemy->hurt = create_sprite_sheet(hurt_name, frame_size.x, frame_size.y,
        2);
    free(walk_name);
    free(shoot_name);
    free(death_name);
    free(hurt_name);
}

void reinit_enemy_sprites(enemy_t *enemy)
{
    enemy_params_t params = get_enemy_params(enemy->type);

    create_enemy_sprite_sheets(enemy, params.name, params.frame_size);
    if (enemy->hp <= 0) {
        enemy->current = enemy->death;
        set_current_frame(enemy->current, enemy->current->frames - 1);
    } else {
        enemy->current = enemy->walk;
        set_current_frame(enemy->current, 0);
    }
}
