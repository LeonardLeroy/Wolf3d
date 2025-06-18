/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** draw_weapon.c
*/

#include "wolf3d.h"

static void apply_weapon_bobbing(sfml_t *sfml)
{
    player_t *player = sfml->game->player;
    sprite_sheet_t *sheet = player->weapon->sheet;
    sfVector2f new_position;

    new_position.x = player->weapon->base_x + player->weapon_bob_x;
    new_position.y = player->weapon->base_y + player->weapon_bob_y;
    sfSprite_setPosition(sheet->sprite, new_position);
}

static void reset_bobbing(sfml_t *sfml)
{
    sfml->game->player->weapon_bob_x = 0.0f;
    sfml->game->player->weapon_bob_y = 0.0f;
}

void draw_weapon(sfml_t *sfml)
{
    if (!sfml->game->player->weapon)
        return;
    if (!sfml->game->player->weapon->shooting)
        apply_weapon_bobbing(sfml);
    else
        reset_bobbing(sfml);
    sfRenderWindow_drawSprite(sfml->window,
        sfml->game->player->weapon->sheet->sprite, NULL);
}
