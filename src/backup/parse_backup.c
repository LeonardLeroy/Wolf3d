/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-evan.lafolie
** File description:
** parse_backup.c
*/

#include "wolf3d.h"

static char *find_json_value(const char *json, const char *key)
{
    char search_pattern[MAX_FILENAME];
    char *pos;

    snprintf(search_pattern, sizeof(search_pattern), "\"%s\":", key);
    pos = strstr(json, search_pattern);
    if (!pos)
        return NULL;
    pos += strlen(search_pattern);
    while (*pos == ' ' || *pos == '\t' || *pos == '\n')
        pos++;
    return pos;
}

float parse_float_value(const char *json, const char *key)
{
    char *pos = find_json_value(json, key);

    if (!pos)
        return 0.0f;
    return atof(pos);
}

int parse_int_value(const char *json, const char *key)
{
    char *pos = find_json_value(json, key);

    if (!pos)
        return 0;
    return atoi(pos);
}

int parse_bool_value(const char *json, const char *key)
{
    char *pos = find_json_value(json, key);

    if (!pos)
        return 0;
    return (strncmp(pos, "true", 4) == 0) ? 1 : 0;
}

void parse_string_value(const char *json, const char *key, char *output,
    int max_len)
{
    char *pos = find_json_value(json, key);
    int i = 0;

    if (!pos)
        return;
    if (*pos == '"')
        pos++;
    while (i < max_len - 1 && pos[i] != '"' && pos[i] != '\0') {
        output[i] = pos[i];
        i++;
    }
    output[i] = '\0';
}

static char *find_data_start(const char *json)
{
    char *data_start = strstr(json, "\"data\": [");

    if (!data_start)
        return NULL;
    return data_start + strlen("\"data\": [");
}

static int parse_row_data(char **pos, int row[MAP_WIDTH])
{
    int x = 0;

    while (**pos && **pos != '[')
        (*pos)++;
    if (**pos != '[')
        return 0;
    (*pos)++;
    while (**pos && x < MAP_WIDTH && **pos != ']') {
        if (**pos >= '0' && **pos <= '9') {
            row[x] = **pos - '0';
            x++;
        }
        (*pos)++;
    }
    return x;
}

static void skip_to_next_row(char **pos)
{
    while (**pos && **pos != ']')
        (*pos)++;
    if (**pos == ']')
        (*pos)++;
}

void parse_map_data(const char *json, int map[MAP_HEIGHT][MAP_WIDTH])
{
    char *pos = find_data_start(json);
    int y = 0;

    if (!pos)
        return;
    while (*pos && y < MAP_HEIGHT) {
        if (parse_row_data(&pos, map[y]) > 0)
            y++;
        skip_to_next_row(&pos);
    }
}
