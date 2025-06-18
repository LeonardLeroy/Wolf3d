/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** update_options.c
*/

#include "wolf3d.h"

static void render_music_and_sfx(sfml_t *sfml, options_t *opt)
{
    sfRenderWindow_drawSprite(sfml->window, opt->sfx_label->sprite, NULL);
    sfRenderWindow_drawSprite(sfml->window, opt->sfx_minus->sprite, NULL);
    sfRenderWindow_drawSprite(sfml->window, opt->sfx_plus->sprite, NULL);
    sfRenderWindow_drawSprite(sfml->window,
        opt->sfx_volume_text[opt->sfx_volume]->sprite, NULL);
    sfRenderWindow_drawSprite(sfml->window, opt->music_label->sprite, NULL);
    sfRenderWindow_drawSprite(sfml->window, opt->music_minus->sprite, NULL);
    sfRenderWindow_drawSprite(sfml->window, opt->music_plus->sprite, NULL);
    sfRenderWindow_drawSprite(sfml->window,
        opt->music_volume_text[opt->music_volume]->sprite, NULL);
}

void render_options(sfml_t *sfml)
{
    options_t *opt = sfml->menu->options;
    sfSprite *sprite;

    sfRenderWindow_setView(sfml->window, sfml->game->cameras->camMenu);
    sfRenderWindow_drawSprite(sfml->window, opt->exit->sprite, NULL);
    sfRenderWindow_drawSprite(sfml->window, opt->fullscreen_label->sprite,
        NULL);
    sprite = (opt->is_fullscreen) ? opt->fullscreen_no->sprite :
        opt->fullscreen_yes->sprite;
    sfRenderWindow_drawSprite(sfml->window, sprite, NULL);
    render_music_and_sfx(sfml, opt);
    sfRenderWindow_drawSprite(sfml->window, opt->framerate_label->sprite,
        NULL);
    sfRenderWindow_drawSprite(sfml->window, opt->framerate_minus->sprite,
        NULL);
    sfRenderWindow_drawSprite(sfml->window, opt->framerate_plus->sprite, NULL);
    sfRenderWindow_drawSprite(sfml->window,
        opt->framerate_text[opt->framerate_index]->sprite, NULL);
    sfRenderWindow_drawSprite(sfml->window, opt->load_button->sprite, NULL);
}

void update_options(sfml_t *sfml)
{
    sfRenderWindow_drawSprite(sfml->window, sfml->menu->bg_sprite, NULL);
    render_color(sfml);
    render_options(sfml);
}
