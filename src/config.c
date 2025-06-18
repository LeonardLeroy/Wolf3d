/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-evan.lafolie
** File description:
** config.c
*/

#include "wolf3d.h"

config_t *init_default_config(void)
{
    config_t *config = salloc(sizeof(config_t));

    if (!config)
        return NULL;
    config->window_width = DEFAULT_WINDOW_WIDTH;
    config->window_height = DEFAULT_WINDOW_HEIGHT;
    config->window_title = strdup(DEFAULT_WINDOW_TITLE);
    config->framerate = DEFAULT_FRAMERATE;
    config->map_width = DEFAULT_MAP_SIZE;
    config->map_height = DEFAULT_MAP_SIZE;
    config->save_file = NULL;
    config->music_volume = DEFAULT_MUSIC_VOLUME;
    config->sfx_volume = DEFAULT_SFX_VOLUME;
    config->use_vsync = 1;
    if (!config->window_title) {
        free(config);
        return NULL;
    }
    return config;
}

void destroy_config(config_t *config)
{
    if (!config)
        return;
    if (config->window_title)
        free(config->window_title);
    if (config->save_file)
        free(config->save_file);
    free(config);
}

static int validate_range(int value, int min, int max)
{
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}

void validate_config(config_t *config)
{
    if (!config)
        return;
    config->window_width = validate_range(config->window_width,
        MIN_WINDOW_WIDTH, MAX_WINDOW_WIDTH);
    config->window_height = validate_range(config->window_height,
        MIN_WINDOW_HEIGHT, MAX_WINDOW_HEIGHT);
    config->framerate = validate_range(config->framerate,
        MIN_FRAMERATE, MAX_FRAMERATE);
    config->music_volume = validate_range(config->music_volume,
        MIN_VOLUME, MAX_VOLUME);
    config->sfx_volume = validate_range(config->sfx_volume,
        MIN_VOLUME, MAX_VOLUME);
}

static int str_equals(const char *str1, const char *str2, const char *str3)
{
    return (strcmp(str1, str2) == 0 || strcmp(str1, str3) == 0) ? 1 : 0;
}

static int handle_volume_options(char **argv, int *i, int argc,
    config_t *config)
{
    if (str_equals(argv[*i], "-vm", "--vol_music") && *i + 1 < argc) {
        (*i)++;
        config->music_volume = atoi(argv[*i]);
        return 0;
    }
    if (str_equals(argv[*i], "-vs", "--vol_sfx") && *i + 1 < argc) {
        (*i)++;
        config->sfx_volume = atoi(argv[*i]);
        return 0;
    }
    return -1;
}

static int handle_extended_options(char **argv, int *i, int argc,
    config_t *config)
{
    if (str_equals(argv[*i], "-l", "--load") && *i + 1 < argc) {
        if (config->save_file)
            free(config->save_file);
        (*i)++;
        config->save_file = strdup(argv[*i]);
        if (!config->save_file)
            return -1;
        return 0;
    }
    return handle_volume_options(argv, i, argc, config);
}

static int handle_size_options(char **argv, int *i, int argc, config_t *config)
{
    if (str_equals(argv[*i], "-w", "--width") && *i + 1 < argc) {
        (*i)++;
        config->window_width = atoi(argv[*i]);
        return 0;
    }
    if (str_equals(argv[*i], "-hg", "--height") && *i + 1 < argc) {
        (*i)++;
        config->window_height = atoi(argv[*i]);
        return 0;
    }
    return handle_extended_options(argv, i, argc, config);
}

static int handle_options(char **argv, int *i, int argc, config_t *config)
{
    if (str_equals(argv[*i], "-h", "--help"))
        return 1;
    if (str_equals(argv[*i], "-t", "--title") && *i + 1 < argc) {
        if (config->window_title)
            free(config->window_title);
        (*i)++;
        config->window_title = strdup(argv[*i]);
        if (!config->window_title)
            return -1;
        return 0;
    }
    if (str_equals(argv[*i], "-f", "--framerate") && *i + 1 < argc) {
        (*i)++;
        config->framerate = atoi(argv[*i]);
        if (config->framerate > 0)
            config->use_vsync = 0;
        return 0;
    }
    return handle_size_options(argv, i, argc, config);
}

int parse_args(int argc, char **argv, config_t *config)
{
    int result;

    if (!config)
        return -1;
    for (int i = 1; i < argc; i++) {
        result = handle_options(argv, &i, argc, config);
        if (result == 1)
            return 1;
        if (result == -1) {
            fprintf(stderr, "Error: Invalid argument '%s' or missing value.\n",
                argv[i]);
            fprintf(stderr, "Use -h or --help for usage information.\n");
            return -1;
        }
    }
    validate_config(config);
    return 0;
}
