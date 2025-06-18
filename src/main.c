/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** main.c
*/

#include "wolf3d.h"

static int handle_parse_result(int argc, char **argv, config_t **config)
{
    int parse_result;

    *config = init_default_config();
    if (!*config) {
        fprintf(stderr, "Error: Failed to initialize configuration.\n");
        return 84;
    }
    parse_result = parse_args(argc, argv, *config);
    if (parse_result == 1) {
        print_help();
        destroy_config(*config);
        return 0;
    }
    if (parse_result == -1) {
        destroy_config(*config);
        return 84;
    }
    return 1;
}

static void create_configured_window(sfml_t *sfml, config_t *config)
{
    sfml->window = sfRenderWindow_create(
        (sfVideoMode){config->window_width, config->window_height, 32},
        config->window_title, sfResize | sfClose, NULL
    );
    if (config->use_vsync)
        sfRenderWindow_setVerticalSyncEnabled(sfml->window, 1);
    else {
        sfRenderWindow_setVerticalSyncEnabled(sfml->window, 0);
        sfRenderWindow_setFramerateLimit(sfml->window, config->framerate);
    }
    sfRenderWindow_setMouseCursorVisible(sfml->window, 0);
}

static void apply_config_to_sfml(sfml_t *sfml, config_t *config)
{
    update_window_size(sfml, config->window_width, config->window_height);
    if (sfml->menu && sfml->menu->options) {
        sfml->menu->options->music_volume = config->music_volume / 10;
        sfml->menu->options->sfx_volume = config->sfx_volume / 10;
        set_music_volume(sfml, config->music_volume);
        set_sfx_volume(sfml, config->sfx_volume);
    }
}

static void load_save_if_specified(sfml_t *sfml, config_t *config)
{
    save_data_t data = {0};

    if (!config->save_file)
        return;
    if (parse_json_file(config->save_file, &data) == 0) {
        apply_save_data(sfml, &data);
        printf("Successfully loaded save file: %s\n", config->save_file);
        play_sound(sfml, "menu_select", 75);
        switch_state(sfml, (switch_state_args_t){GAME, &update_game,
            &game_events});
    } else {
        printf("Warning: Failed to load save file: %s\n", config->save_file);
        printf("Starting with default game state.\n");
    }
}

static int initialize_application(int ac, char **av, sfml_t *sfml,
    config_t **config)
{
    int result;

    result = handle_parse_result(ac, av, config);
    if (result != 1)
        return result;
    init_window_size(sfml);
    update_window_size(sfml, (*config)->window_width,
    (*config)->window_height);
    create_configured_window(sfml, *config);
    init_sfml(sfml);
    apply_config_to_sfml(sfml, *config);
    handle_window_resize(sfml);
    load_save_if_specified(sfml, *config);
    return 1;
}

int main(int ac, char **av)
{
    sfml_t sfml = {0};
    config_t *config = NULL;
    int result;

    result = initialize_application(ac, av, &sfml, &config);
    if (result != 1)
        return result;
    while (sfRenderWindow_isOpen(sfml.window)) {
        while (sfRenderWindow_pollEvent(sfml.window, &sfml.event))
            events(&sfml);
        sfRenderWindow_clear(sfml.window, sfBlack);
        update(&sfml);
        sfRenderWindow_display(sfml.window);
    }
    destroy_config(config);
    free_sfml(&sfml);
    return 0;
}
