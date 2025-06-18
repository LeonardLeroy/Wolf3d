/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-evan.lafolie
** File description:
** enemy_parser.c
*/

#include "wolf3d.h"

static void parse_enemy_position(const char *json_section, enemy_t *enemy)
{
    char *enemy_start = (char *)json_section;
    char *pos = enemy_start;

    pos = parse_float_field(json_section, pos, "\"x\":", &enemy->x);
    pos = parse_float_field(json_section, pos, "\"y\":", &enemy->y);
    enemy_start = (char *)json_section;
    pos = enemy_start;
    pos = parse_float_field(json_section, pos, "\"world_x\":",
        &enemy->world_x);
    pos = parse_float_field(json_section, pos, "\"world_y\":",
        &enemy->world_y);
}

static void parse_enemy_hp_and_type(const char *json_section, enemy_t *enemy)
{
    char *pos = (char *)json_section;
    int type_value;

    parse_int_field(json_section, pos, "\"hp\":", &enemy->hp);
    pos = strstr(json_section, "\"type\":");
    if (pos) {
        sscanf(pos + 7, " %d", &type_value);
        enemy->type = (enum ENEMY)type_value;
    }
}

static void parse_single_enemy(const char *json_section, enemy_t *enemy)
{
    char *pos = (char *)json_section;

    parse_enemy_position(json_section, enemy);
    parse_float_field(json_section, pos, "\"angle\":", &enemy->angle);
    parse_enemy_hp_and_type(json_section, enemy);
}

static int parse_enemies_count(const char *enemies_section)
{
    char *count_pos = strstr(enemies_section, "\"count\":");
    int count = 0;

    if (!count_pos)
        return 0;
    sscanf(count_pos + 8, " %d", &count);
    return count;
}

static bool parse_enemy_at_position(char **current_pos, enemy_t *enemy)
{
    char *enemy_end;
    size_t enemy_length;
    char *enemy_json;

    *current_pos = strstr(*current_pos, "{");
    if (!*current_pos)
        return false;
    enemy_end = strstr(*current_pos, "}");
    if (!enemy_end)
        return false;
    enemy_length = enemy_end - *current_pos + 1;
    enemy_json = malloc(enemy_length + 1);
    if (!enemy_json)
        return false;
    strncpy(enemy_json, *current_pos, enemy_length);
    enemy_json[enemy_length] = '\0';
    parse_single_enemy(enemy_json, enemy);
    free(enemy_json);
    *current_pos = enemy_end + 1;
    return true;
}

static void parse_all_enemies(char *data_start, save_data_t *data)
{
    char *current_pos = data_start;

    for (int i = 0; i < data->enemies_count && i < NUM_ENEMIES; i++) {
        if (!parse_enemy_at_position(&current_pos, &data->enemies[i])) {
            data->enemies_count = i;
            break;
        }
    }
}

void parse_enemies_data(const char *json, save_data_t *data)
{
    char *enemies_section = strstr(json, "\"enemies\":");
    char *data_start;

    if (!enemies_section) {
        data->enemies_count = 0;
        return;
    }
    data->enemies_count = parse_enemies_count(enemies_section);
    if (data->enemies_count == 0)
        return;
    data_start = strstr(enemies_section, "\"data\": [");
    if (!data_start) {
        data->enemies_count = 0;
        return;
    }
    parse_all_enemies(data_start, data);
}
