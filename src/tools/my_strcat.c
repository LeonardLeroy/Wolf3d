/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** my_strcat.c
*/

#include "wolf3d.h"

char *my_strcat(char const *text1, char const *text2)
{
    int size1 = strlen(text1);
    int size2 = strlen(text2);
    char *res = salloc(size1 + size2 + 1);

    if (!text1 || !text2)
        return NULL;
    if (!res)
        return NULL;
    for (int i = 0; i < size1; i++)
        res[i] = text1[i];
    for (int i = 0; i < size2; i++)
        res[size1 + i] = text2[i];
    res[size1 + size2] = '\0';
    return res;
}
