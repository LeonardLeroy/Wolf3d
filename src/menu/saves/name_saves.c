/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-evan.lafolie
** File description:
** name_saves.c
*/

#include "wolf3d.h"

static char get_char_index(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c == '-')
        return 10;
    if (c == '_')
        return 11;
    return -1;
}

void cleanup_name_sprites(saves_t *saves)
{
    if (!saves->name_sprites)
        return;
    for (int i = 0; i < saves->name_sprites_count; i++) {
        if (saves->name_sprites[i])
            sfSprite_destroy(saves->name_sprites[i]);
    }
    free(saves->name_sprites);
    saves->name_sprites = NULL;
}

static int extract_save_name(saves_t *saves, char *name, size_t name_size)
{
    char *dot;

    if (saves->save_count == 0 ||
        saves->selected_save_index >= saves->save_count)
        return -1;
    strncpy(name, saves->save_files[saves->selected_save_index],
        name_size - 1);
    name[name_size - 1] = '\0';
    dot = strrchr(name, '.');
    if (dot)
        *dot = '\0';
    if (strncmp(name, "save", 4) == 0)
        memmove(name, name + 4, strlen(name + 4) + 1);
    return strlen(name);
}

static void calculate_layout(sfml_t *sfml, int valid_count,
    layout_info_t *layout)
{
    float total_width;
    sfVector2u window_size;

    layout->scale = get_scale_factor(sfml);
    layout->char_width = 15 * layout->scale * 3.00f;
    layout->save_width = 65 * layout->scale * 3.00f;
    total_width = layout->save_width + (valid_count * layout->char_width);
    window_size = sfRenderWindow_getSize(sfml->window);
    layout->start_x = (window_size.x - total_width) / 2.0f;
    layout->y = (START_Y + SPACING * 1.8f) * sfml->window_size->scale_factor_y;
}

static int create_save_prefix_sprite(saves_t *saves,
    const layout_info_t *layout)
{
    saves->name_sprites[0] = sfSprite_create();
    if (!saves->name_sprites[0])
        return 84;
    sfSprite_setTexture(saves->name_sprites[0], saves->save_texture, sfTrue);
    sfSprite_setScale(saves->name_sprites[0],
        (sfVector2f){layout->scale * 3.00f, layout->scale * 3.00f});
    sfSprite_setPosition(saves->name_sprites[0],
        (sfVector2f){layout->start_x, layout->y});
    return 0;
}

static sfSprite *create_single_character_sprite(saves_t *saves, int char_index,
    float x_pos, const layout_info_t *layout)
{
    sfSprite *sprite = sfSprite_create();
    sfVector2f scale;
    sfVector2f position;

    if (!sprite)
        return NULL;
    sfSprite_setTexture(sprite, saves->char_sprites[char_index]->texture,
        sfTrue);
    scale = (sfVector2f){layout->scale * 3.00f, layout->scale * 3.00f};
    sfSprite_setScale(sprite, scale);
    position = (sfVector2f){x_pos, layout->y};
    sfSprite_setPosition(sprite, position);
    return sprite;
}

static int create_character_sprites(saves_t *saves, const char *name, int len,
    const layout_info_t *layout)
{
    int sprite_index = 1;
    float current_x = layout->start_x + layout->save_width;
    int char_index;

    for (int i = 0; i < len && sprite_index < saves->name_sprites_count; i++) {
        char_index = get_char_index(name[i]);
        if (!(char_index >= 0 && char_index < 12))
            continue;
        saves->name_sprites[sprite_index] =
        create_single_character_sprite(saves, char_index, current_x, layout);
        if (saves->name_sprites[sprite_index]) {
            current_x += layout->char_width;
            sprite_index++;
        }
    }
    return sprite_index;
}

static int extract_and_validate_save_name(saves_t *saves, char *name,
    size_t name_size, int *valid_count)
{
    int len = extract_save_name(saves, name, name_size);
    int temp_valid_count = 0;

    if (len <= 0)
        return -1;
    for (int i = 0; i < len; i++) {
        if (get_char_index(name[i]) >= 0)
            temp_valid_count++;
    }
    *valid_count = temp_valid_count;
    if (*valid_count == 0)
        return -1;
    return len;
}

static int initialize_sprite_array(saves_t *saves, int valid_count)
{
    saves->name_sprites_count = valid_count + 1;
    saves->name_sprites = salloc(sizeof(sfSprite *) *
        saves->name_sprites_count);
    if (!saves->name_sprites) {
        saves->name_sprites_count = 0;
        return -1;
    }
    return 0;
}

void create_name_sprites(sfml_t *sfml, saves_t *saves)
{
    char name[256];
    int valid_count;
    int name_len;
    layout_info_t layout;
    int final_count;

    cleanup_name_sprites(saves);
    name_len = extract_and_validate_save_name(saves, name, sizeof(name),
        &valid_count);
    if (name_len < 0)
        return;
    if (initialize_sprite_array(saves, valid_count))
        return;
    calculate_layout(sfml, valid_count, &layout);
    if (create_save_prefix_sprite(saves, &layout) != 0) {
        cleanup_name_sprites(saves);
        return;
    }
    final_count = create_character_sprites(saves, name, name_len, &layout);
    saves->name_sprites_count = final_count;
}
