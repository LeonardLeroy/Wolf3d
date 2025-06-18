/*
** EPITECH PROJECT, 2024
** wolf3d
** File description:
** draw_hud.c
*/

#include "wolf3d.h"

void draw_hud_text_value(sfml_t *sfml, sfText *text, int x)
{
    sfVector2u win = sfRenderWindow_getSize(sfml->window);
    float y = win.y - (win.y / 6);

    sfText_setPosition(text, (sfVector2f){x, y});
    sfRenderWindow_drawText(sfml->window, text, NULL);
    sfText_destroy(text);
}

static sfText *create_sf_text_hud(sfml_t *sfml, unsigned int font_size,
    char *buffer)
{
    sfText *text;

    text = sfText_create();
    sfText_setFont(text, sfml->fonts->doom_ui);
    sfText_setCharacterSize(text, font_size);
    sfText_setString(text, buffer);
    return text;
}

void draw_hud_value(sfml_t *sfml, int value, int x,
    int is_percentage)
{
    char buffer[8];
    sfText *text_shadow;
    sfText *text;
    sfVector2u window_size = sfRenderWindow_getSize(sfml->window);
    unsigned int font_size = window_size.y / 10;

    if (is_percentage)
        snprintf(buffer, sizeof(buffer), "%03d%%", value);
    else
        snprintf(buffer, sizeof(buffer), "%03d", value);
    text_shadow = create_sf_text_hud(sfml, font_size, buffer);
    sfText_setColor(text_shadow, sfColor_fromRGB(0, 0, 0));
    draw_hud_text_value(sfml, text_shadow, x + 6);
    text = create_sf_text_hud(sfml, font_size, buffer);
    sfText_setColor(text, sfColor_fromRGB(180, 180, 180));
    draw_hud_text_value(sfml, text, x);
}

static void draw_hud_hp(sfml_t *sfml, sfVector2u window_size)
{
    int hp = sfml->game->player->hp;
    int x = window_size.x / 5.55f;

    draw_hud_value(sfml, hp, x, 1);
}

static void draw_hud_armor(sfml_t *sfml, sfVector2u window_size)
{
    int armor = sfml->game->player->armor;
    int x = window_size.x / 1.72f;

    draw_hud_value(sfml, armor, x, 1);
}

static int get_ammo_count(player_t *player)
{
    switch (player->weapon->type) {
        case PISTOL:
        case CHAINGUN:
            return (player->ammo.bullets);
        case SHOTGUN:
        case SUPER_SHOTGUN:
            return (player->ammo.shells);
        default:
            return (0);
    }
}

static void draw_hud_ammo(sfml_t *sfml, sfVector2u window_size)
{
    player_t *player = sfml->game->player;
    int ammo_count = get_ammo_count(player);
    int x = window_size.x / 32.5f;

    draw_hud_value(sfml, ammo_count, x, 0);
}

static void draw_hud_frags(sfml_t *sfml, sfVector2u window_size)
{
    player_t *player = sfml->game->player;
    int frags = player->frags;
    int x = window_size.x / 2.925f;

    draw_hud_value(sfml, frags, x, 0);
}

void draw_hud_text(sfml_t *sfml)
{
    sfVector2u window_size;

    window_size = sfRenderWindow_getSize(sfml->window);
    draw_hud_frags(sfml, window_size);
    draw_hud_hp(sfml, window_size);
    draw_hud_armor(sfml, window_size);
    if (sfml->game->player->weapon->type != FIST)
        draw_hud_ammo(sfml, window_size);
}

void draw_hud(sfml_t *sfml)
{
    sfRenderWindow_drawSprite(sfml->window, sfml->game->hud->stbar, NULL);
    sfRenderWindow_drawSprite(sfml->window, sfml->game->hud->doom_guy, NULL);
    draw_hud_text(sfml);
}
