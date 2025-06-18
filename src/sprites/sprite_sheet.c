/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** sprite_sheet.c
*/

#include "wolf3d.h"

static void init_offsets(sfVector2i *offsets, int width,
    int frames)
{
    for (int i = 0; i < frames; i++) {
        offsets[i].x = i * width;
        offsets[i].y = 0;
    }
}

sprite_sheet_t *create_sprite_sheet(char const *img, int width,
    int height, int frames)
{
    sprite_sheet_t *sheet = salloc(sizeof(sprite_sheet_t));

    sheet->width = width;
    sheet->height = height;
    sheet->frames = frames;
    sheet->texture = sfTexture_createFromFile(image(img), NULL);
    sheet->sprite = sfSprite_create();
    sfSprite_setTexture(sheet->sprite, sheet->texture, sfTrue);
    sheet->offsets = salloc(frames * sizeof(sfVector2i));
    init_offsets(sheet->offsets, width, frames);
    set_current_frame(sheet, 0);
    sheet->anim_timer = 0.0f;
    return sheet;
}

void free_sprite_sheet(sprite_sheet_t *sheet)
{
    if (!sheet)
        return;
    sfTexture_destroy(sheet->texture);
    sheet->texture = NULL;
    sfSprite_destroy(sheet->sprite);
    sheet->sprite = NULL;
    free(sheet->offsets);
    sheet->offsets = NULL;
    free(sheet);
    sheet = NULL;
}

void set_current_frame(sprite_sheet_t *sheet, int frame)
{
    if (frame < 0)
        frame = 0;
    if (frame >= sheet->frames)
        frame = sheet->frames - 1;
    sheet->current_frame = frame;
    sfSprite_setTextureRect(sheet->sprite, (sfIntRect)
        {sheet->offsets[frame].x, sheet->offsets[frame].y,
        sheet->width, sheet->height});
}
