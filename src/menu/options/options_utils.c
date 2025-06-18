/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** options_utils.c
*/

#include "wolf3d.h"

menu_button_t *create_button_with_scale(char const *texture_path, float scale)
{
    menu_button_t *button = salloc(sizeof(menu_button_t));

    button->texture = sfTexture_createFromFile(image(texture_path), NULL);
    button->sprite = sfSprite_create();
    sfSprite_setTexture(button->sprite, button->texture, sfTrue);
    sfSprite_setScale(button->sprite, (sfVector2f){scale, scale});
    button->bounds = sfSprite_getGlobalBounds(button->sprite);
    return button;
}

void position_plus_button(menu_button_t *percentage,
    menu_button_t *plus_button)
{
    float percent_x;
    float y_position;
    float scale;
    float plus_x;
    float percentage_width;
    float consistent_spacing;

    if (!percentage || !plus_button)
        return;
    percent_x = sfSprite_getPosition(percentage->sprite).x;
    y_position = sfSprite_getPosition(percentage->sprite).y;
    scale = sfSprite_getScale(percentage->sprite).x;
    percentage_width = sfSprite_getGlobalBounds(percentage->sprite).width;
    consistent_spacing = 30 * scale;
    plus_x = percent_x + percentage_width + consistent_spacing;
    sfSprite_setPosition(plus_button->sprite,
        (sfVector2f){plus_x, y_position});
    plus_button->bounds = sfSprite_getGlobalBounds(plus_button->sprite);
}

void set_music_volume(sfml_t *sfml, int volume)
{
    if (sfml->music) {
        sfMusic_setVolume(sfml->music->menu_music, volume);
        sfMusic_setVolume(sfml->music->music, volume);
    }
}

void set_sfx_volume(sfml_t *sfml, int volume)
{
    if (!sfml->sound)
        return;
    sfml->sound->sfx_volume = volume;
    for (int i = 0; i < MAX_SOUND_BUFFER; i++) {
        if (sfml->sound->sound_player[i])
            sfSound_setVolume(sfml->sound->sound_player[i]->sound, volume);
    }
}

static void get_window_settings(sfml_t *sfml, sfVideoMode *mode,
    sfWindowStyle *style)
{
    if (sfml->menu->options->is_fullscreen) {
        mode->width = WINDOW_WIDTH;
        mode->height = WINDOW_HEIGHT;
        mode->bitsPerPixel = 32;
        *style = sfClose;
        sfml->menu->options->is_fullscreen = 0;
    } else {
        *mode = sfVideoMode_getDesktopMode();
        *style = sfFullscreen;
        sfml->menu->options->is_fullscreen = 1;
    }
}

static void recreate_window(sfml_t *sfml, sfVideoMode mode,
    sfWindowStyle style)
{
    sfRenderWindow_destroy(sfml->window);
    free_cameras(sfml);
    free_hud(sfml);
    sfml->window = sfRenderWindow_create(mode, "Wolf3d", style, NULL);
    init_hud(sfml);
    init_cameras(sfml);
    sfRenderWindow_setVerticalSyncEnabled(sfml->window, 1);
}

void toggle_fullscreen(sfml_t *sfml)
{
    sfVideoMode mode;
    sfWindowStyle style;

    get_window_settings(sfml, &mode, &style);
    recreate_window(sfml, mode, style);
    sfRenderWindow_setMouseCursorVisible(sfml->window, 0);
    if (sfml->state == GAME)
        recenter_mouse(sfml);
}
