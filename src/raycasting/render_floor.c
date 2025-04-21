/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** render_floor.c
*/

#include "wolf3d.h"

// void render_floor(sfml_t *sfml)
// {
//     sfTexture *floor_texture = sfTexture_createFromFile(image("floor"),
//         NULL);
//     sfSprite *floor = sfSprite_create();
//     sfVector2u tex_size = sfTexture_getSize(floor_texture);
//     sfVector2u window_size = sfRenderWindow_getSize(sfml->window);
//     sfVector2f scale = {
//         (float)window_size.x / tex_size.x,
//         (float)(window_size.y / 2) / tex_size.y
//     };

//     sfTexture_setSmooth(floor_texture, sfFalse);
//     sfSprite_setTexture(floor, floor_texture, sfTrue);
//     sfSprite_setScale(floor, scale);
//     sfSprite_setPosition(floor, (sfVector2f){0, window_size.y / 2});
//     sfRenderWindow_drawSprite(sfml->window, floor, NULL);
//     sfSprite_destroy(floor);
//     sfTexture_destroy(floor_texture);
// }

void render_floor(sfml_t *sfml)
{
    sfVector2u window_size = sfRenderWindow_getSize(sfml->window);
    sfRectangleShape *floor = sfRectangleShape_create();

    sfRectangleShape_setSize(floor,
        (sfVector2f){window_size.x, window_size.y / 2});
    sfRectangleShape_setFillColor(floor,
        sfColor_fromRGB(0, 0, 50));
    sfRectangleShape_setPosition(floor,
        (sfVector2f){0, window_size.y / 2});
    sfRenderWindow_drawRectangleShape(sfml->window, floor, NULL);
    sfRectangleShape_destroy(floor);
}
