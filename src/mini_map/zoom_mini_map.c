/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** zoom_mini_map.c
*/

#include "wolf3d.h"

static void zoom_in(sfml_t *sfml)
{
    sfVector2f prev_size = sfView_getSize(sfml->game->cameras->camGame);
    float zoom_factor = 0.975f;

    sfView_setSize(sfml->game->cameras->camGame,
        (sfVector2f){prev_size.x * zoom_factor, prev_size.y * zoom_factor});
}

static void zoom_out(sfml_t *sfml)
{
    sfVector2f prev_size = sfView_getSize(sfml->game->cameras->camGame);
    float zoom_factor = 1.025f;

    sfView_setSize(sfml->game->cameras->camGame,
        (sfVector2f){prev_size.x * zoom_factor, prev_size.y * zoom_factor});
}

static void check_zoom(sfml_t *sfml)
{
    sfVector2f current_size = sfView_getSize(sfml->game->cameras->camGame);

    if (current_size.x < MINI_MAP_MIN_ZOOM_X ||
        current_size.y < MINI_MAP_MIN_ZOOM_Y) {
        sfView_setSize(sfml->game->cameras->camGame,
            (sfVector2f){MINI_MAP_MIN_ZOOM_X, MINI_MAP_MIN_ZOOM_Y});
    } else if (current_size.x > MINI_MAP_MAX_ZOOM_X ||
        current_size.y > MINI_MAP_MAX_ZOOM_Y) {
        sfView_setSize(sfml->game->cameras->camGame,
            (sfVector2f){MINI_MAP_MAX_ZOOM_X, MINI_MAP_MAX_ZOOM_Y});
    }
}

void mini_map_zoom(sfml_t *sfml)
{
    if (sfml->game->game_substate != MINI_MAP)
        return;
    if (sfml->event.mouseWheelScroll.delta > 0)
        zoom_in(sfml);
    else if (sfml->event.mouseWheelScroll.delta < 0)
        zoom_out(sfml);
    check_zoom(sfml);
}

void mini_map_zoom_controller(sfml_t *sfml)
{
    float dpad = sfJoystick_getAxisPosition(CONTROLLER_ID, sfJoystickPovY);

    if (dpad > 0)
        zoom_in(sfml);
    else if (dpad < 0)
        zoom_out(sfml);
    check_zoom(sfml);
}
