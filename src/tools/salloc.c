/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** salloc.c
*/

#include "wolf3d.h"

void *salloc(size_t size)
{
    void *ptr = NULL;

    if (size <= 0 || size > INT32_MAX)
        return NULL;
    for (int i = 0; i < 5; i++) {
        ptr = malloc(size);
        if (ptr != NULL)
            break;
    }
    return ptr;
}
