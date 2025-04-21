/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** paths.c
*/

#include "wolf3d.h"

char *image(const char *img)
{
    static char buffer[MAX_PATH];
    const char *prefix = "assets/images/";
    const char *ext = IMAGE_EXT;
    size_t prefix_len = 14;
    size_t img_len = strlen(img);
    size_t ext_len = strlen(ext);

    if (prefix_len + img_len + ext_len >= MAX_PATH)
        return NULL;
    strcpy(buffer, prefix);
    cat(buffer, img);
    cat(buffer, ext);
    return buffer;
}

char *font(const char *font)
{
    static char buffer[MAX_PATH];
    const char *prefix = "assets/fonts/";
    const char *ext = ".ttf";
    size_t prefix_len = 13;
    size_t font_len = strlen(font);
    size_t ext_len = 4;

    if (prefix_len + font_len + ext_len >= MAX_PATH)
        return NULL;
    strcpy(buffer, prefix);
    cat(buffer, font);
    cat(buffer, ext);
    return buffer;
}

char *file(const char *text, const char *format)
{
    static char buffer[MAX_PATH];
    size_t text_len = strlen(text);
    size_t format_len = strlen(format);

    if (text_len + format_len >= MAX_PATH)
        return NULL;
    strcpy(buffer, text);
    cat(buffer, format);
    return buffer;
}

char *sound(const char *snd)
{
    static char buffer[MAX_PATH];
    const char *prefix = "assets/sounds/";
    const char *ext = SOUND_EXT;
    size_t prefix_len = 14;
    size_t snd_len = strlen(snd);
    size_t ext_len = strlen(ext);

    if (prefix_len + snd_len + ext_len >= MAX_PATH)
        return NULL;
    strcpy(buffer, prefix);
    cat(buffer, snd);
    cat(buffer, ext);
    return buffer;
}

char *music(const char *msc)
{
    static char buffer[MAX_PATH];
    const char *prefix = "assets/music/";
    const char *ext = SOUND_EXT;
    size_t prefix_len = 14;
    size_t msc_len = strlen(msc);
    size_t ext_len = strlen(ext);

    if (prefix_len + msc_len + ext_len >= MAX_PATH)
        return NULL;
    strcpy(buffer, prefix);
    cat(buffer, msc);
    cat(buffer, ext);
    return buffer;
}
