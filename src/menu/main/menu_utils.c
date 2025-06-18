/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** menu_util.c
*/

#include "wolf3d.h"

menu_button_t *create_menu_button(sfml_t *sfml, char const *texture_path,
    int n)
{
    menu_button_t *button = salloc(sizeof(menu_button_t));
    float y = (n != -1) ? (450 + (120 * n)) : 0;

    button->texture = sfTexture_createFromFile(image(texture_path), NULL);
    button->sprite = sfSprite_create();
    sfSprite_setTexture(button->sprite, button->texture, sfTrue);
    sfSprite_setScale(button->sprite, (n != -1) ?
        (sfVector2f){4.6, 5} : (sfVector2f){3.5, 3.5});
    sfSprite_setPosition(button->sprite, (sfVector2f){
        (n != -1) ? sfSprite_getPosition(sfml->menu->doom_sprite).x + 5 : 0,
        y});
    button->bounds = sfSprite_getGlobalBounds(button->sprite);
    return button;
}

void render_color(sfml_t *sfml)
{
    sfVector2u window = sfRenderWindow_getSize(sfml->window);
    sfRectangleShape *rect = sfRectangleShape_create();

    sfRectangleShape_setSize(rect, (sfVector2f){window.x, window.y});
    sfRectangleShape_setFillColor(rect, (sfColor){70, 51, 35, 128});
    sfRenderWindow_drawRectangleShape(sfml->window, rect, NULL);
    sfRectangleShape_destroy(rect);
}

void change_bg_sprite(sfml_t *sfml)
{
    sfVector2u window_size = sfRenderWindow_getSize(sfml->window);
    sfTexture *temp_texture = sfTexture_create(window_size.x, window_size.y);
    sfImage *image;

    sfTexture_updateFromRenderWindow(temp_texture, sfml->window, 0, 0);
    image = sfTexture_copyToImage(temp_texture);
    sfTexture_destroy(temp_texture);
    sfTexture_destroy(sfml->menu->bg_texture);
    sfml->menu->bg_texture = sfTexture_createFromImage(image, NULL);
    sfSprite_setTexture(sfml->menu->bg_sprite, sfml->menu->bg_texture, sfTrue);
    sfSprite_setScale(sfml->menu->bg_sprite, (sfVector2f){1, 1});
    sfSprite_setPosition(sfml->menu->bg_sprite, (sfVector2f){0, 0});
    sfImage_destroy(image);
}
