/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** mouse.c
*/

#include "wolf3d.h"

void update_mouse(sfml_t *sfml)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(sfml->window);

    sfSprite_setPosition(sfml->cursor->sprite, (sfVector2f){
        mouse_pos.x, mouse_pos.y
    });
    sfRenderWindow_drawSprite(sfml->window, sfml->cursor->sprite, NULL);
}

void init_cursor(sfml_t *sfml)
{
    sfml->cursor = salloc(sizeof(sprite_t));
    sfml->cursor->sprite = sfSprite_create();
    sfml->cursor->texture = sfTexture_createFromFile(image("cursor"), NULL);
    sfSprite_setTexture(sfml->cursor->sprite, sfml->cursor->texture, sfTrue);
}

void free_cursor(sfml_t *sfml)
{
    if (!sfml->cursor)
        return;
    sfTexture_destroy(sfml->cursor->texture);
    sfml->cursor->texture = NULL;
    sfSprite_destroy(sfml->cursor->sprite);
    sfml->cursor->sprite = NULL;
    free(sfml->cursor);
    sfml->cursor = NULL;
}
