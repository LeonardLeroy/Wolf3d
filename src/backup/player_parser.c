/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-evan.lafolie
** File description:
** player_parser.c
*/

#include "wolf3d.h"

static void parse_player_momentum(const char *json_content, save_data_t *data)
{
    char *momentum_section = strstr(json_content, "\"momentum\":");
    char *x_pos;
    char *y_pos;

    if (momentum_section) {
        x_pos = strstr(momentum_section, "\"x\":");
        y_pos = strstr(momentum_section, "\"y\":");
        if (x_pos)
            sscanf(x_pos + 4, " %f", &data->player.momentum_x);
        if (y_pos)
            sscanf(y_pos + 4, " %f", &data->player.momentum_y);
    }
}

void parse_player_data(const char *json_content, save_data_t *data)
{
    data->player.x = parse_float_value(json_content, "x");
    data->player.y = parse_float_value(json_content, "y");
    data->player.angle = parse_float_value(json_content, "angle");
    parse_player_momentum(json_content, data);
    data->player.hp = parse_int_value(json_content, "health");
    data->player.armor = parse_int_value(json_content, "armor");
    data->player.frags = parse_int_value(json_content, "frags");
    data->player.ammo.bullets = parse_int_value(json_content, "ammo_normal");
    data->player.ammo.shells = parse_int_value(json_content, "ammo_shotgun");
    data->player.bob_phase = parse_float_value(json_content, "bob_phase");
    data->player.height_offset = parse_float_value(json_content,
        "height_offset");
}
