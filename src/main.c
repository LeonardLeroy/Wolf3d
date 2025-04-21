/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** main.c
*/

#include "wolf3d.h"

int main(int ac, char **av)
{
    sfml_t sfml = {0};

    if (ac != 1) {
        fprintf(stderr, "Usage: %s\n", av[0]);
        return 84;
    }
    init_sfml(&sfml);
    while (sfRenderWindow_isOpen(sfml.window)) {
        while (sfRenderWindow_pollEvent(sfml.window, &sfml.event))
            events(&sfml);
        sfRenderWindow_clear(sfml.window, sfBlack);
        draw(&sfml);
        update(&sfml);
        sfRenderWindow_display(sfml.window);
    }
    free_sfml(&sfml);
    return 0;
}
