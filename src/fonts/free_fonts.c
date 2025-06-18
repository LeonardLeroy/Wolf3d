/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** free_fonts.c
*/

#include "wolf3d.h"

void free_fonts(sfml_t *sfml)
{
    if (!sfml->fonts)
        return;
    if (sfml->fonts->eternal_ui) {
        sfFont_destroy(sfml->fonts->eternal_ui);
        sfml->fonts->eternal_ui = NULL;
    }
    if (sfml->fonts->doom_ui) {
        sfFont_destroy(sfml->fonts->doom_ui);
        sfml->fonts->doom_ui = NULL;
    }
    free(sfml->fonts);
    sfml->fonts = NULL;
}
