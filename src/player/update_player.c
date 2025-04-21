/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** update_player.c
*/

#include "wolf3d.h"

/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** update_player.c
*/

#include "wolf3d.h"

static int keyboard_movement(void)
{
    if (sfKeyboard_isKeyPressed(sfKeyZ)
        || sfKeyboard_isKeyPressed(sfKeyUp)
        || sfKeyboard_isKeyPressed(sfKeyS)
        || sfKeyboard_isKeyPressed(sfKeyDown)
        || sfKeyboard_isKeyPressed(sfKeyQ)
        || sfKeyboard_isKeyPressed(sfKeyD))
        return 1;
    return 0;
}

static void handle_mouse_movement(sfml_t *sfml)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(sfml->window);
    sfVector2u window_size = sfRenderWindow_getSize(sfml->window);
    int center_x = window_size.x / 2;
    int center_y = window_size.y / 2;
    float rotation;
    float movement;

    if (mouse_pos.x != center_x) {
        rotation = (mouse_pos.x - center_x) * MOUSE_SENSITIVITY;
        sfml->game->player->angle += rotation;
        sfml->game->player->angle = normalize_angle(sfml->game->player->angle);
    }
    if (mouse_pos.y != center_y && !keyboard_movement()) {
        movement = (center_y - mouse_pos.y) * MOUSE_SENSITIVITY * 10;
        move_player(sfml, movement, sfml->game->player->angle);
    }
    sfMouse_setPositionRenderWindow((sfVector2i){center_x, center_y},
        sfml->window);
}

static void update_player_rotation(sfml_t *sfml)
{
    if (sfKeyboard_isKeyPressed(sfKeyLeft)) {
        sfml->game->player->angle -= ROTATION_SPEED;
        sfml->game->player->angle = normalize_angle(sfml->game->player->angle);
    }
    if (sfKeyboard_isKeyPressed(sfKeyRight)) {
        sfml->game->player->angle += ROTATION_SPEED;
        sfml->game->player->angle = normalize_angle(sfml->game->player->angle);
    }
    handle_mouse_movement(sfml);
}

static void update_player_movement(sfml_t *sfml)
{
    float current_speed = MOVEMENT_SPEED;

    if (sfKeyboard_isKeyPressed(sfKeyLShift) ||
        sfKeyboard_isKeyPressed(sfKeyRShift))
        current_speed = SPRINT_SPEED;
    if (sfKeyboard_isKeyPressed(sfKeyUp) || sfKeyboard_isKeyPressed(sfKeyZ))
        move_player(sfml, current_speed, sfml->game->player->angle);
    if (sfKeyboard_isKeyPressed(sfKeyDown) || sfKeyboard_isKeyPressed(sfKeyS))
        move_player(sfml, current_speed, sfml->game->player->angle - PI);
    if (sfKeyboard_isKeyPressed(sfKeyQ))
        move_player(sfml, current_speed, sfml->game->player->angle - PI / 2);
    if (sfKeyboard_isKeyPressed(sfKeyD))
        move_player(sfml, current_speed, sfml->game->player->angle + PI / 2);
}

void update_player(sfml_t *sfml)
{
    update_player_rotation(sfml);
    update_player_movement(sfml);
}
