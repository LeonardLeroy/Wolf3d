/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** transition.c
*/

#include "wolf3d.h"

static void save_screen_sprite(sfml_t *sfml, sfSprite **sprite,
    sfTexture **texture)
{
    sfVector2u window_size = sfRenderWindow_getSize(sfml->window);
    sfTexture *temp_texture = sfTexture_create(window_size.x, window_size.y);
    sfImage *image;

    sfTexture_updateFromRenderWindow(temp_texture, sfml->window, 0, 0);
    image = sfTexture_copyToImage(temp_texture);
    sfTexture_destroy(temp_texture);
    if (*texture)
        sfTexture_destroy(*texture);
    *texture = sfTexture_createFromImage(image, NULL);
    if (*sprite)
        sfSprite_destroy(*sprite);
    *sprite = sfSprite_create();
    sfSprite_setTexture(*sprite, *texture, sfTrue);
    sfSprite_setScale(*sprite, (sfVector2f){1, 1});
    sfSprite_setPosition(*sprite, (sfVector2f){0, 0});
    sfImage_destroy(image);
}

static void init_transition_sprites(sfml_t *sfml)
{
    int columns = sfml->window_size->width / 15;

    sfml->transition->columns_count = columns;
    sfml->transition->columns = salloc(sizeof(sfSprite *) * columns);
    for (int i = 0; i < columns; i++) {
        sfml->transition->columns[i] = sfSprite_copy(sfml->transition->front);
        sfSprite_setPosition(sfml->transition->columns[i], (sfVector2f){
            i * 15.0f, 0.0f
        });
        sfSprite_setTextureRect(sfml->transition->columns[i], (sfIntRect){
            i * 15, 0, 15, sfml->window_size->height
        });
    }
}

void init_transition(sfml_t *sfml)
{
    sfml->transition = salloc(sizeof(transition_t));
    memset(sfml->transition, 0, sizeof(transition_t));
    sfml->transition->active = 0;
    sfml->transition->transition_timer = 0.0f;
    sfml->transition->back = sfSprite_create();
    sfml->transition->back_texture = sfTexture_create(
        sfml->window_size->width, sfml->window_size->height
    );
    sfml->transition->front = sfSprite_create();
    sfml->transition->front_texture = sfTexture_create(
        sfml->window_size->width, sfml->window_size->height
    );
}

static void handle_start_transition(sfml_t *sfml)
{
    sfRenderWindow_clear(sfml->window, sfBlack);
    update_enemies(sfml, sfml->game->ai_manager);
    draw_enemies(sfml);
    draw_game(sfml);
    save_screen_sprite(sfml, &sfml->transition->back,
        &sfml->transition->back_texture);
    sfRenderWindow_clear(sfml->window, sfBlack);
    sfRenderWindow_drawSprite(sfml->window, sfml->menu->bg_sprite, NULL);
    save_screen_sprite(sfml, &sfml->transition->front,
        &sfml->transition->front_texture);
    init_transition_sprites(sfml);
    sfml->transition->active = 1;
}

static int verify_transition_status(sfml_t *sfml)
{
    for (int i = 0; i < sfml->transition->columns_count; i++) {
        if (sfSprite_getPosition(sfml->transition->columns[i]).y <
            sfml->window_size->height)
            return 0;
    }
    return 1;
}

int handle_transition(sfml_t *sfml)
{
    if (!sfml->transition->active) {
        handle_start_transition(sfml);
        return 0;
    }
    sfRenderWindow_clear(sfml->window, sfBlack);
    sfRenderWindow_drawSprite(sfml->window, sfml->transition->back, NULL);
    for (int i = 0; i < sfml->transition->columns_count; i++) {
        if (sfSprite_getPosition(sfml->transition->columns[i]).y > 0 ||
            rand() % 4 == 0)
            sfSprite_move(sfml->transition->columns[i], (sfVector2f){
                0.0f, 8
            });
        sfRenderWindow_drawSprite(sfml->window,
            sfml->transition->columns[i], NULL);
    }
    sfRenderWindow_display(sfml->window);
    return verify_transition_status(sfml);
}

static void free_columns(sfml_t *sfml)
{
    for (int i = 0; i < sfml->transition->columns_count; i++) {
        if (sfml->transition->columns[i])
            sfSprite_destroy(sfml->transition->columns[i]);
    }
}

void handle_transition_state(sfml_t *sfml)
{
    int end = 0;

    if (sfml->music->current == sfml->music->menu_music)
        change_music(sfml, sfml->music->music);
    if (sfml->transition->active) {
        free_transition(sfml);
        init_transition(sfml);
    }
    while (!end)
        end = handle_transition(sfml);
    sfml->menu->game_started = 1;
}

void free_transition(sfml_t *sfml)
{
    if (!sfml->transition)
        return;
    if (sfml->transition->columns) {
        free_columns(sfml);
        free(sfml->transition->columns);
    }
    if (sfml->transition->back)
        sfSprite_destroy(sfml->transition->back);
    if (sfml->transition->back_texture)
        sfTexture_destroy(sfml->transition->back_texture);
    if (sfml->transition->front)
        sfSprite_destroy(sfml->transition->front);
    if (sfml->transition->front_texture)
        sfTexture_destroy(sfml->transition->front_texture);
    free(sfml->transition);
    sfml->transition = NULL;
}
