/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-evan.lafolie
** File description:
** json_parser.c
*/

#include "wolf3d.h"

char *parse_float_field(const char *json_section, char *start_pos,
    const char *field_name, float *value)
{
    char *pos = strstr(start_pos ? start_pos : json_section, field_name);

    if (pos) {
        sscanf(pos + strlen(field_name), " %f", value);
        return pos + 1;
    }
    return start_pos;
}

char *parse_int_field(const char *json_section, char *start_pos,
    const char *field_name, int *value)
{
    char *pos = strstr(start_pos ? start_pos : json_section, field_name);

    if (pos) {
        sscanf(pos + strlen(field_name), " %d", value);
        return pos + 1;
    }
    return start_pos;
}
