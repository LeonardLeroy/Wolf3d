/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** render_ceiling.c
*/

#include "wolf3d.h"

// void render_ceiling(sfml_t *sfml)
// {
//     sfTexture *ceiling_texture = sfTexture_createFromFile(image("ceiling"),
//         NULL);
//     sfSprite *ceiling = sfSprite_create();
//     sfVector2u tex_size = sfTexture_getSize(ceiling_texture);
//     sfVector2u window_size = sfRenderWindow_getSize(sfml->window);
//     sfVector2f scale = {
//         (float)window_size.x / tex_size.x,
//         (float)(window_size.y / 2) / tex_size.y
//     };

//     sfTexture_setSmooth(ceiling_texture, sfFalse);
//     sfSprite_setTexture(ceiling, ceiling_texture, sfTrue);
//     sfSprite_setScale(ceiling, scale);
//     sfSprite_setPosition(ceiling, (sfVector2f){0, 0});
//     sfRenderWindow_drawSprite(sfml->window, ceiling, NULL);
//     sfSprite_destroy(ceiling);
//     sfTexture_destroy(ceiling_texture);
// }

void render_ceiling(sfml_t *sfml)
{
    sfRectangleShape *ceiling = sfRectangleShape_create();
    sfVector2u window_size = sfRenderWindow_getSize(sfml->window);

    sfRectangleShape_setSize(ceiling,
        (sfVector2f){window_size.x, window_size.y / 2});
    sfRectangleShape_setFillColor(ceiling,
        sfColor_fromRGB(51, 26, 15));
    sfRectangleShape_setPosition(ceiling,
        (sfVector2f){0, 0});
    sfRenderWindow_drawRectangleShape(sfml->window, ceiling, NULL);
    sfRectangleShape_destroy(ceiling);
}
