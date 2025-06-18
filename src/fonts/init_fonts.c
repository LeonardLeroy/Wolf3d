/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** init_fonts.c
*/

#include "wolf3d.h"

void init_fonts(sfml_t *sfml)
{
    sfml->fonts = salloc(sizeof(fonts_t));
    sfml->fonts->eternal_ui = sfFont_createFromFile(font("eternal_ui"));
    sfml->fonts->doom_ui = sfFont_createFromFile(font("doom"));
}
