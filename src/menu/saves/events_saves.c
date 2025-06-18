/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-evan.lafolie
** File description:
** events_saves.c
*/

#include "wolf3d.h"

static void navigate_saves(sfml_t *sfml, int direction)
{
    saves_t *saves = sfml->menu->saves;

    if (saves->save_count <= 0)
        return;
    saves->selected_save_index += direction;
    if (saves->selected_save_index < 0)
        saves->selected_save_index = saves->save_count - 1;
    else if (saves->selected_save_index >= saves->save_count)
        saves->selected_save_index = 0;
    create_name_sprites(sfml, saves);
    position_arrows(sfml, saves);
    play_sound(sfml, "menu_select", 100);
}

static void load_selected_save(sfml_t *sfml)
{
    saves_t *saves = sfml->menu->saves;
    save_data_t data = {0};

    if (saves->save_count <= 0 ||
        saves->selected_save_index >= saves->save_count) {
        printf("No save selected!\n");
        return;
    }
    if (parse_json_file(saves->save_files[saves->selected_save_index],
        &data) == 0) {
        apply_save_data(sfml, &data);
        printf("Game loaded successfully!\n");
        play_sound(sfml, "menu_select", 75);
        switch_state(sfml, (switch_state_args_t){GAME, &update_game,
            &game_events});
    } else
        printf("Failed to load game!\n");
}

static int is_any_key_pressed(void)
{
    return (sfKeyboard_isKeyPressed(sfKeyLeft) ||
        sfKeyboard_isKeyPressed(sfKeyRight) ||
        sfKeyboard_isKeyPressed(sfKeyEnter) ||
        sfKeyboard_isKeyPressed(sfKeySpace) ||
        sfKeyboard_isKeyPressed(sfKeyEscape));
}

static void handle_keyboard_input(sfml_t *sfml)
{
    static int was_pressed = 0;

    if (is_any_key_pressed() && !was_pressed) {
        if (sfKeyboard_isKeyPressed(sfKeyLeft))
            navigate_saves(sfml, -1);
        if (sfKeyboard_isKeyPressed(sfKeyRight))
            navigate_saves(sfml, 1);
        if (sfKeyboard_isKeyPressed(sfKeyEnter) ||
            sfKeyboard_isKeyPressed(sfKeySpace))
            load_selected_save(sfml);
        if (sfKeyboard_isKeyPressed(sfKeyEscape)) {
            play_sound(sfml, "menu_cancel", 100);
            switch_menu_substate(sfml, (switch_menu_substate_args_t)
                {OPTIONS, &update_options, &events_options});
        }
        was_pressed = 1;
    }
    if (sfml->event.type == sfEvtKeyReleased && was_pressed)
        was_pressed = 0;
}

static void handle_save_click(saves_t *saves, sfml_t *sfml)
{
    play_sound(sfml, "menu_select", 100);
    if (save_game(sfml) != 0) {
        printf("Failed to save game!\n");
        return;
    }
    printf("Game saved successfully!\n");
    if (saves->save_files) {
        for (int i = 0; i < saves->save_count; i++)
            free(saves->save_files[i]);
        free(saves->save_files);
    }
    cleanup_name_sprites(saves);
    load_saves_list(saves);
    create_name_sprites(sfml, saves);
    position_arrows(sfml, saves);
    return;
}

static int handle_name_click(saves_t *saves, sfml_t *sfml,
    sfVector2i mouse_pos)
{
    sfFloatRect bounds;

    for (int i = 0; i < saves->name_sprites_count; i++) {
        if (!saves->name_sprites || !saves->name_sprites[i])
            continue;
        bounds = sfSprite_getGlobalBounds(saves->name_sprites[i]);
        if (sfFloatRect_contains(&bounds, mouse_pos.x, mouse_pos.y)) {
            load_selected_save(sfml);
            return 1;
        }
    }
    return 0;
}

static void handle_arrow_click(saves_t *saves, sfml_t *sfml,
    sfVector2i mouse_pos)
{
    if (saves->save_count > 1) {
        if (saves->arrow_left && saves->arrow_left->sprite &&
            sfFloatRect_contains(&saves->arrow_left->bounds,
                mouse_pos.x, mouse_pos.y)) {
            navigate_saves(sfml, -1);
            return;
        }
        if (saves->arrow_right && saves->arrow_right->sprite &&
            sfFloatRect_contains(&saves->arrow_right->bounds, mouse_pos.x,
                mouse_pos.y)) {
            navigate_saves(sfml, 1);
            return;
        }
    }
    handle_name_click(saves, sfml, mouse_pos);
}

static void handle_back_click(saves_t *saves, sfml_t *sfml,
    sfVector2i mouse_pos)
{
    if (saves->back_button && sfFloatRect_contains(&saves->back_button->bounds,
        mouse_pos.x, mouse_pos.y)) {
        play_sound(sfml, "menu_cancel", 100);
        switch_menu_substate(sfml, (switch_menu_substate_args_t)
            {OPTIONS, &update_options, &events_options});
        return;
    }
    handle_arrow_click(saves, sfml, mouse_pos);
}

static void handle_mouse_input(sfml_t *sfml)
{
    saves_t *saves = sfml->menu->saves;
    sfVector2i mouse_pos;

    if (!saves)
        return;
    mouse_pos = sfMouse_getPositionRenderWindow(sfml->window);
    if (sfml->event.type != sfEvtMouseButtonPressed ||
        sfml->event.mouseButton.button != sfMouseLeft) {
        return;
    }
    if (saves->save_button && sfFloatRect_contains(&saves->save_button->bounds,
        mouse_pos.x, mouse_pos.y)) {
        handle_save_click(saves, sfml);
    }
    if (saves->load_button && sfFloatRect_contains(&saves->load_button->bounds,
        mouse_pos.x, mouse_pos.y)) {
        load_selected_save(sfml);
        return;
    }
    handle_back_click(saves, sfml, mouse_pos);
}

void events_saves(sfml_t *sfml)
{
    handle_keyboard_input(sfml);
    handle_mouse_input(sfml);
}
