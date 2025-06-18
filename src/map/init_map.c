/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** init_map.c
*/

#include "wolf3d.h"

static void fill_map_line(sfml_t *sfml, char *line, int i)
{
    char *token = strtok(line, " \n");
    int j = 1;

    while (token != NULL) {
        if (token[0] == '0' || token[0] == '1') {
            sfml->game->map[i][j] = token[0] - '0';
            j++;
        }
        token = strtok(NULL, " \n");
    }
}

static void determine_file_map(sfml_t *sfml, FILE *file)
{
    char *line = NULL;
    size_t len = 0;

    for (int i = 1; i < MAP_HEIGHT - 1; i++) {
        if (getline(&line, &len, file) == -1) {
            free(line);
            line = NULL;
            break;
        }
        fill_map_line(sfml, line, i);
        free(line);
        line = NULL;
    }
}

void init_map(sfml_t *sfml, FILE *file)
{
    if (file == NULL) {
        generate_procedural_map(sfml);
        return;
    }
    determine_file_map(sfml, file);
    sfml->game->map[1][1] = 0;
}
