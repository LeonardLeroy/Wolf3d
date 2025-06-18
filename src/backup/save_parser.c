/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-evan.lafolie
** File description:
** save_parser.c
*/

#include "wolf3d.h"

static void parse_data(char *json, save_data_t *data)
{
    parse_enemies_data(json, data);
    data->flashlight_active = parse_bool_value(json, "flashlight_active");
    data->muzzle_flash_timer = parse_float_value(json, "muzzle_flash_timer");
    data->music_volume = parse_int_value(json, "music_volume");
    data->sfx_volume = parse_int_value(json, "sfx_volume");
    data->window_width = parse_int_value(json, "window_width");
    data->window_height = parse_int_value(json, "window_height");
    data->is_fullscreen = parse_bool_value(json, "is_fullscreen");
    data->framerate_index = parse_int_value(json, "framerate_index");
    data->camera_center_x = parse_float_value(json, "camera_center_x");
    data->camera_center_y = parse_float_value(json, "camera_center_y");
    data->precise_minimap_zoom = parse_float_value(json,
        "precise_minimap_zoom");
}

int parse_json_file(const char *filename, save_data_t *data)
{
    char *json_content;

    if (!filename || !data)
        return 84;
    json_content = read_json_file(filename);
    if (!json_content)
        return 84;
    parse_string_value(json_content, "version", data->version,
        sizeof(data->version));
    parse_string_value(json_content, "timestamp", data->timestamp,
        sizeof(data->timestamp));
    data->play_time = parse_float_value(json_content, "play_time");
    parse_player_data(json_content, data);
    parse_map_data(json_content, data->map);
    data->minimap_zoom = parse_float_value(json_content, "zoom_level");
    data->minimap_active = parse_bool_value(json_content, "is_active");
    parse_data(json_content, data);
    free(json_content);
    printf("Successfully loaded save: %s\n", filename);
    return 0;
}
