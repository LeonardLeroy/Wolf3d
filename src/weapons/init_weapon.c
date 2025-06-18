/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** init_weapon.c
*/

#include "wolf3d.h"

static sprite_sheet_t *load_sheet_from_weapon_type(enum WEAPONS type)
{
    switch (type) {
        case FIST:
            return create_sprite_sheet("weapons/fist", 230, 76, 6);
        case SHOTGUN:
            return create_sprite_sheet("weapons/shotgun", 119, 151, 9);
        case SUPER_SHOTGUN:
            return create_sprite_sheet("weapons/super_shotgun", 201, 130, 13);
        case CHAINGUN:
            return create_sprite_sheet("weapons/chaingun", 114, 103, 3);
        default:
            return create_sprite_sheet("weapons/pistol", 78, 103, 5);
    }
}

float get_x_weapon_offset(enum WEAPONS type)
{
    switch (type) {
        case PISTOL:
            return 52.0f;
        case SHOTGUN:
            return 15.0f;
        case SUPER_SHOTGUN:
            return 5.0f;
        case CHAINGUN:
            return 5.0f;
        default:
            return 0.0f;
    }
}

float get_y_weapon_offset(enum WEAPONS type)
{
    switch (type) {
        case CHAINGUN:
            return -120.0f;
        default:
            return 0.0f;
    }
}

sfVector2f calculate_weapon_position(sfml_t *sfml, weapon_t *weapon)
{
    sfVector2f hud_pos = sfSprite_getPosition(sfml->game->hud->stbar);
    float weapon_scale = sfSprite_getScale(weapon->sheet->sprite).y;
    float weapon_y = hud_pos.y - (weapon->sheet->height * weapon_scale * 0.9f)
        - get_y_weapon_offset(weapon->type) *
            sfml->window_size->scale_factor_y;
    float weapon_x = get_centered_x(sfml, weapon->sheet->sprite) -
        get_x_weapon_offset(weapon->type) * sfml->window_size->scale_factor_x;

    return (sfVector2f){weapon_x, weapon_y};
}

weapon_t *init_weapon(sfml_t *sfml, int type)
{
    weapon_t *weapon = salloc(sizeof(weapon_t));
    float scale = get_scale_factor(sfml);
    sfVector2f weapon_pos;

    weapon->type = (enum WEAPONS)type;
    weapon->sheet = load_sheet_from_weapon_type(weapon->type);
    sfSprite_setScale(weapon->sheet->sprite, (sfVector2f){4.0f * scale,
        4.0f * scale});
    weapon_pos = calculate_weapon_position(sfml, weapon);
    sfSprite_setPosition(weapon->sheet->sprite, weapon_pos);
    weapon->base_x = weapon_pos.x;
    weapon->base_y = weapon_pos.y;
    weapon->shooting = 0;
    return weapon;
}

// TO ADD A WEAPON:
// 1. add +1 to WEAPONS_AMOUNT
// 2. insert it's name to the enum WEAPONS
// 3. add a new case in load_sheet_from_weapon_type
// 4. add a new element to the sfml->game->weapons list here
// 5. don't forget the sound and sprite sheet in assets folder
// PS: if necessary, add x/y offsets to the weapon's position
// IMPORTANT: THE WEAPONS INITIALIZED HERE MUST
// MATCH THE ORDER OF THE ENUM TABLE, OR IT WILL CRASH!!
void init_weapons(sfml_t *sfml)
{
    sfml->game->weapons = salloc(sizeof(weapon_t *) * WEAPONS_AMOUNT);
    sfml->game->weapons[FIST] = init_weapon(sfml, FIST);
    sfml->game->weapons[PISTOL] = init_weapon(sfml, PISTOL);
    sfml->game->weapons[SHOTGUN] = init_weapon(sfml, SHOTGUN);
    sfml->game->weapons[SUPER_SHOTGUN] = init_weapon(sfml, SUPER_SHOTGUN);
    sfml->game->weapons[CHAINGUN] = init_weapon(sfml, CHAINGUN);
    sfml->game->player->weapon = sfml->game->weapons[PISTOL];
}
