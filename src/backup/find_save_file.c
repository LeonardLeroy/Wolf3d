/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-evan.lafolie
** File description:
** find_save_file.c
*/

#include "wolf3d.h"
#include <stdbool.h>

int compare_save_files(const void *a, const void *b)
{
    return strcmp(*(const char **)b, *(const char **)a);
}

static char **resize_saves_array(char **saves, int new_capacity)
{
    char **new_saves = realloc(saves, sizeof(char *) * new_capacity);

    return new_saves;
}

static bool add_save_filename(char ***saves, int *count,
    int *capacity, const char *filename)
{
    char **new_saves;

    if (*count >= *capacity) {
        *capacity *= 2;
        new_saves = resize_saves_array(*saves, *capacity);
        if (!new_saves)
            return false;
        *saves = new_saves;
    }
    (*saves)[*count] = malloc(strlen(filename) + 1);
    if (!(*saves)[*count])
        return false;
    strcpy((*saves)[*count], filename);
    (*count)++;
    return true;
}

static void free_saves_array(char **saves, int count)
{
    if (saves) {
        for (int i = 0; i < count; i++)
            free(saves[i]);
        free(saves);
    }
}

static DIR *open_save_directory(void)
{
    DIR *dir = opendir(SAVE_DIR);

    if (!dir)
        printf("No save directory found.\n");
    return dir;
}

static bool collect_save_files(DIR *dir, char ***saves, int *count,
    int *capacity)
{
    struct dirent *entry = readdir(dir);

    while (entry != NULL) {
        if (strstr(entry->d_name, "save_") && strstr(entry->d_name, ".json") &&
        !add_save_filename(saves, count, capacity, entry->d_name))
            return false;
        entry = readdir(dir);
    }
    return true;
}

static char **close_and_return(DIR *dir)
{
    closedir(dir);
    return NULL;
}

char **list_save_files(int *count)
{
    DIR *dir;
    char **saves = NULL;
    int capacity = 10;

    *count = 0;
    dir = open_save_directory();
    if (!dir)
        return NULL;
    saves = malloc(sizeof(char *) * capacity);
    if (!saves)
        return close_and_return(dir);
    if (!collect_save_files(dir, &saves, count, &capacity)) {
        free_saves_array(saves, *count);
        return close_and_return(dir);
    }
    closedir(dir);
    if (*count > 0)
        qsort(saves, *count, sizeof(char *), compare_save_files);
    return saves;
}
