/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-evan.lafolie
** File description:
** init_saves.c
*/

#include "wolf3d.h"

static void init_char_sprites(saves_t *saves)
{
    const char *char_names[] = {
        "options/load_0", "options/load_1", "options/load_2", "options/load_3",
        "options/load_4", "options/load_5", "options/load_6", "options/load_7",
        "options/load_8", "options/load_9", "options/load_-", "options/load__"
    };

    for (int i = 0; i < 12; i++) {
        saves->char_sprites[i] = salloc(sizeof(char_sprite_t));
        if (!saves->char_sprites[i])
            continue;
        saves->char_sprites[i]->texture = sfTexture_createFromFile(
            image(char_names[i]), NULL);
        if (!saves->char_sprites[i]->texture)
            continue;
        saves->char_sprites[i]->sprite = sfSprite_create();
        if (saves->char_sprites[i]->sprite) {
            sfSprite_setTexture(saves->char_sprites[i]->sprite,
                saves->char_sprites[i]->texture, sfTrue);
        }
    }
}

static void init_arrow(menu_button_t *arrow, float scale_x, float scale_y)
{
    arrow->texture = sfTexture_createFromFile(image("options/m_arrow"), NULL);
    if (arrow->texture) {
        arrow->sprite = sfSprite_create();
        if (arrow->sprite) {
            sfSprite_setTexture(arrow->sprite, arrow->texture, sfTrue);
            sfSprite_setScale(arrow->sprite, (sfVector2f){scale_x * 3.0f,
                scale_y * 3.0f});
        }
    }
}

static void init_navigation_arrows(sfml_t *sfml, saves_t *saves)
{
    float scale = get_scale_factor(sfml);

    saves->arrow_left = salloc(sizeof(menu_button_t));
    if (saves->arrow_left)
        init_arrow(saves->arrow_left, scale, scale);
    saves->arrow_right = salloc(sizeof(menu_button_t));
    if (saves->arrow_right)
        init_arrow(saves->arrow_right, -scale, scale);
}

static void init_button(menu_button_t *button, float factor_x,
    float factor_y)
{
    sfSprite_setPosition(button->sprite, (sfVector2f){
        factor_x, factor_y});
    button->bounds = sfSprite_getGlobalBounds(button->sprite);
}

static void init_saves_buttons(sfml_t *sfml, saves_t *saves)
{
    float scale = get_scale_factor(sfml);
    sfVector2u window_size = sfRenderWindow_getSize(sfml->window);

    saves->save_button = create_button_with_scale("options/o_save",
        4.75f * scale);
    init_button(saves->save_button,
        LEFT_MARGIN * sfml->window_size->scale_factor_x,
        START_Y * sfml->window_size->scale_factor_y);
    saves->load_button = create_button_with_scale("options/o_load",
        4.75f * scale);
    init_button(saves->load_button,
        LEFT_MARGIN * sfml->window_size->scale_factor_x,
        (START_Y + SPACING) * sfml->window_size->scale_factor_x);
    saves->back_button = create_button_with_scale("options/o_exit",
        4.75f * scale);
    init_button(saves->load_button,
        (window_size.x - sfSprite_getGlobalBounds(saves->back_button->sprite)
        .width) / 2.0f,
        (START_Y + SPACING * 4) * sfml->window_size->scale_factor_y);
}

void load_saves_list(saves_t *saves)
{
    saves->save_files = list_save_files(&saves->save_count);
    saves->selected_save_index = 0;
    saves->name_sprites = NULL;
    saves->name_sprites_count = 0;
}

static int valid_position(saves_t *saves)
{
    return (saves->save_count <= 1 || !saves->arrow_left ||
        !saves->arrow_right || !saves->arrow_left->sprite ||
        !saves->arrow_right->sprite);
}

void position_arrows(sfml_t *sfml, saves_t *saves)
{
    float y = (START_Y + SPACING * 1.828f) * sfml->window_size->scale_factor_y;
    float arrow_margin = 70.0f * get_scale_factor(sfml);
    sfFloatRect last_sprite;

    if (valid_position(saves))
        return;
    if (saves->name_sprites_count > 0 && saves->name_sprites[0] &&
        saves->name_sprites[saves->name_sprites_count - 1]) {
        last_sprite = sfSprite_getGlobalBounds(
            saves->name_sprites[saves->name_sprites_count - 1]);
        sfSprite_setPosition(saves->arrow_left->sprite, (sfVector2f)
            {sfSprite_getGlobalBounds(saves->name_sprites[0]).left
                - arrow_margin, y});
        sfSprite_setPosition(saves->arrow_right->sprite,
        (sfVector2f){last_sprite.left + last_sprite.width + arrow_margin, y});
    }
    saves->arrow_left->bounds =
    sfSprite_getGlobalBounds(saves->arrow_left->sprite);
    saves->arrow_right->bounds =
    sfSprite_getGlobalBounds(saves->arrow_right->sprite);
}

void init_saves(sfml_t *sfml)
{
    saves_t *saves;

    sfml->menu->saves = salloc(sizeof(saves_t));
    saves = sfml->menu->saves;
    saves->save_texture = sfTexture_createFromFile(image("options/o_save"),
        NULL);
    init_char_sprites(saves);
    init_navigation_arrows(sfml, saves);
    init_saves_buttons(sfml, saves);
    load_saves_list(saves);
    create_name_sprites(sfml, saves);
    position_arrows(sfml, saves);
}
