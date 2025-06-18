/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-evan.lafolie
** File description:
** load_manager.c
*/

#include "wolf3d.h"

static int load_game(sfml_t *sfml, const char *filename)
{
    save_data_t data = {0};

    if (parse_json_file(filename, &data) != 0)
        return 84;
    apply_save_data(sfml, &data);
    return 0;
}

int list_saves_and_load_latest(sfml_t *sfml)
{
    int count;
    char **saves = list_save_files(&count);
    int result;

    if (!saves || count == 0) {
        printf("No save files found.\n");
        return 84;
    }
    printf("Loading most recent save.\n");
    result = load_game(sfml, saves[0]);
    if (!saves)
        return result;
    for (int i = 0; i < count; i++)
        free(saves[i]);
    free(saves);
    if (result == 0)
        play_sound(sfml, "menu_select", 75);
    return result;
}
