/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** open_map.c
*/

#include "wolf3d.h"

void open_map(sfml_t *sfml, char *filename)
{
    FILE *file = NULL;

    if (filename == NULL) {
        init_map(sfml, NULL);
        return;
    }
    file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open map file: %s\n", filename);
        return;
    }
    init_map(sfml, file);
    fclose(file);
}
