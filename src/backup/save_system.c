/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-evan.lafolie
** File description:
** save_system.c
*/

#include "wolf3d.h"

static int create_save_directory(void)
{
    struct stat st = {0};

    if (stat(SAVE_DIR, &st) == -1)
        return MKDIR(SAVE_DIR);
    return 0;
}

static char *generate_save_filename(void)
{
    static char filename[MAX_FILENAME];
    time_t now;
    struct tm *timeinfo;

    time(&now);
    timeinfo = localtime(&now);
    snprintf(filename, MAX_FILENAME,
        "%ssave_%02d-%02d-%02d_%02d-%02d-%02d.json",
        SAVE_DIR, timeinfo->tm_year % 100,
        timeinfo->tm_mon + 1, timeinfo->tm_mday,
        timeinfo->tm_hour, timeinfo->tm_min,
        timeinfo->tm_sec
    );
    return filename;
}

static void set_save_metadata(save_data_t *data)
{
    time_t now = time(NULL);
    struct tm *timeinfo;

    strcpy(data->version, "1.0");
    timeinfo = localtime(&now);
    snprintf(data->timestamp, 32, "%02d-%02d-%02d_%02d-%02d-%02d",
        timeinfo->tm_year % 100, timeinfo->tm_mon + 1, timeinfo->tm_mday,
        timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
}

static void save_weapons_data(sfml_t *sfml, save_data_t *data)
{
    if (!sfml->game->weapons)
        return;
    for (int i = 0; i < WEAPONS_AMOUNT; i++) {
        if (sfml->game->weapons[i])
            memcpy(&data->weapons[i], sfml->game->weapons[i],
                sizeof(weapon_t));
    }
    data->current_weapon = (sfml->game->player && sfml->game->player->weapon) ?
        sfml->game->player->weapon->type : PISTOL;
}

static void save_camera_data(sfml_t *sfml, save_data_t *data)
{
    sfVector2f size;

    if (!sfml->game->cameras || !sfml->game->cameras->camGame)
        return;
    size = sfView_getSize(sfml->game->cameras->camGame);
    data->minimap_zoom = size.x / WINDOW_WIDTH;
    data->minimap_active = (sfml->game->game_substate == MINI_MAP) ? 1 : 0;
}

static void save_enemies_data(sfml_t *sfml, save_data_t *data)
{
    data->enemies_count = NUM_ENEMIES;
    for (int i = 0; i < NUM_ENEMIES; i++) {
        if (sfml->game->enemies[i]) {
            memcpy(&data->enemies[i], sfml->game->enemies[i], sizeof(enemy_t));
            data->enemies[i].walk = NULL;
            data->enemies[i].shoot = NULL;
            data->enemies[i].death = NULL;
            data->enemies[i].hurt = NULL;
            data->enemies[i].current = NULL;
        }
    }
}

static void save_user_settings_data(sfml_t *sfml, save_data_t *data)
{
    if (sfml->menu && sfml->menu->options) {
        data->music_volume = sfml->menu->options->music_volume;
        data->sfx_volume = sfml->menu->options->sfx_volume;
        data->is_fullscreen = sfml->menu->options->is_fullscreen;
        data->framerate_index = sfml->menu->options->framerate_index;
    }
    if (sfml->window_size) {
        data->window_width = sfml->window_size->width;
        data->window_height = sfml->window_size->height;
    }
}

static void save_interface_state_data(sfml_t *sfml, save_data_t *data)
{
    sfVector2f center;
    sfVector2f size;

    if (sfml->game->cameras && sfml->game->cameras->camGame) {
        center = sfView_getCenter(sfml->game->cameras->camGame);
        data->camera_center_x = center.x;
        data->camera_center_y = center.y;
        size = sfView_getSize(sfml->game->cameras->camGame);
        data->precise_minimap_zoom = size.x / WINDOW_WIDTH;
    }
}

static void collect_save_data(sfml_t *sfml, save_data_t *data)
{
    if (!sfml || !sfml->game || !data)
        return;
    set_save_metadata(data);
    if (sfml->game->player)
        memcpy(&data->player, sfml->game->player, sizeof(player_t));
    memcpy(data->map, sfml->game->map, sizeof(int) * MAP_HEIGHT * MAP_WIDTH);
    save_weapons_data(sfml, data);
    save_camera_data(sfml, data);
    data->play_time = (sfml->clocks) ? sfml->clocks->elapsed : 0.0f;
    save_enemies_data(sfml, data);
    if (sfml->game->player) {
        data->flashlight_active = sfml->game->player->flashlight_active;
        data->muzzle_flash_timer = sfml->game->player->muzzle_flash_timer;
    }
    save_user_settings_data(sfml, data);
    save_interface_state_data(sfml, data);
}

int save_game(sfml_t *sfml)
{
    char *filename;
    save_data_t save_data = {0};
    FILE *file;

    if (!sfml || !sfml->game)
        return 84;
    if (create_save_directory() != 0)
        fprintf(stderr, "Warning: Could not create save directory\n");
    filename = generate_save_filename();
    collect_save_data(sfml, &save_data);
    file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Error: Could not create save file: %s\n", filename);
        return 84;
    }
    write_json_to_file(file, &save_data);
    fclose(file);
    printf("Game saved successfully: %s\n", filename);
    return 0;
}
