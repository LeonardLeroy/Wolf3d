/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** init_menu.c
*/

#include "wolf3d.h"

static void create_title_bg(sfml_t *sfml)
{
    sfVector2u texture_size;
    float scale_x;
    float scale_y;
    float scale;

    sfml->menu->bg_texture = sfTexture_createFromFile(image("menu/titlepic"),
        NULL);
    sfml->menu->bg_sprite = sfSprite_create();
    sfSprite_setTexture(sfml->menu->bg_sprite, sfml->menu->bg_texture, sfTrue);
    texture_size = sfTexture_getSize(sfml->menu->bg_texture);
    scale_x = (float)sfml->window_size->width / texture_size.x;
    scale_y = (float)sfml->window_size->height / texture_size.y;
    scale = (scale_x < scale_y) ? scale_x : scale_y;
    sfSprite_setScale(sfml->menu->bg_sprite, (sfVector2f){scale, scale});
    sfSprite_setPosition(sfml->menu->bg_sprite, (sfVector2f){
        (sfml->window_size->width - (texture_size.x * scale)) / 2,
        (sfml->window_size->height - (texture_size.y * scale)) / 2
    });
}

static void complete_doom_menu(sfml_t *sfml)
{
    create_title_bg(sfml);
    sfml->menu->doom_texture = sfTexture_createFromFile(image("menu/m_doom"),
        NULL);
    sfml->menu->doom_sprite = sfSprite_create();
    sfSprite_setTexture(sfml->menu->doom_sprite, sfml->menu->doom_texture,
        sfTrue);
    sfSprite_setScale(sfml->menu->doom_sprite, (sfVector2f){4.75f, 5.75f});
    sfSprite_setPosition(sfml->menu->doom_sprite,
        (sfVector2f){get_centered_x(sfml, sfml->menu->doom_sprite) - 5, 10});
    sfml->menu->skull_sheet = create_sprite_sheet("menu/skull", 20, 19, 2);
    sfSprite_setScale(sfml->menu->skull_sheet->sprite,
        (sfVector2f){3.5f, 4.0f});
    sfml->menu->start_b = create_menu_button(sfml, "menu/m_start", 0);
    sfml->menu->options_b = create_menu_button(sfml, "menu/m_options", 1);
    sfml->menu->exit_b = create_menu_button(sfml, "menu/m_exit", 2);
    sfml->menu->back_b = create_menu_button(sfml, "menu/m_back", -1);
    sfSprite_setPosition(sfml->menu->skull_sheet->sprite, (sfVector2f)
        {sfSprite_getPosition(sfml->menu->start_b->sprite).x - 100,
            sfSprite_getPosition(sfml->menu->start_b->sprite).y});
}

void init_menu(sfml_t *sfml)
{
    sfml->menu = salloc(sizeof(menu_t));
    sfml->menu->menu_substate = MAIN;
    sfml->menu->game_started = 0;
    sfml->menu->intro = 1;
    complete_doom_menu(sfml);
    init_options(sfml);
    init_saves(sfml);
}
