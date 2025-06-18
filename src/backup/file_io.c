/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-evan.lafolie
** File description:
** file_io.c
*/

#include "wolf3d.h"

static char *read_file_content(FILE *file)
{
    long file_size = 0;
    char *content;
    size_t bytes_read;

    if (fseek(file, 0, SEEK_END) != 0)
        return NULL;
    file_size = ftell(file);
    if (file_size == -1 || fseek(file, 0, SEEK_SET) != 0)
        return NULL;
    content = malloc(file_size + 1);
    if (!content)
        return NULL;
    bytes_read = fread(content, 1, file_size, file);
    if (bytes_read != (size_t) file_size) {
        free(content);
        return NULL;
    }
    content[file_size] = '\0';
    return content;
}

char *read_json_file(const char *filename)
{
    char full_path[MAX_FULLPATH];
    FILE *file;
    char *json_content;

    snprintf(full_path, sizeof(full_path), "%s%s", SAVE_DIR, filename);
    file = fopen(full_path, "r");
    if (!file) {
        printf("Error: Could not open save file: %s\n", full_path);
        return NULL;
    }
    json_content = read_file_content(file);
    if (!json_content) {
        fclose(file);
        return NULL;
    }
    fclose(file);
    return json_content;
}
