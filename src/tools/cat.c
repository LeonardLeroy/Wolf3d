/*
** EPITECH PROJECT, 2025
** my_world
** File description:
** cat.c
*/

void cat(char *dest, const char *src)
{
    while (*dest)
        ++dest;
    while (*src) {
        *dest = *src;
        ++dest;
        ++src;
    }
    *dest = '\0';
}
