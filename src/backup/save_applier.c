/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-evan.lafolie
** File description:
** save_applier.c
*/

#include "wolf3d.h"

static void apply_player_data(sfml_t *sfml, save_data_t *data)
{
    if (!sfml->game->player)
        return;
    sfml->game->player->x = data->player.x;
    sfml->game->player->y = data->player.y;
    sfml->game->player->angle = data->player.angle;
    sfml->game->player->momentum_x = data->player.momentum_x;
    sfml->game->player->momentum_y = data->player.momentum_y;
    sfml->game->player->hp = data->player.hp;
    sfml->game->player->armor = data->player.armor;
    sfml->game->player->frags = data->player.frags;
    sfml->game->player->ammo.bullets = data->player.ammo.bullets;
    sfml->game->player->ammo.shells = data->player.ammo.shells;
    sfml->game->player->bob_phase = data->player.bob_phase;
    sfml->game->player->height_offset = data->player.height_offset;
    sfml->game->player->weapon_bob_x = 0.0f;
    sfml->game->player->weapon_bob_y = 0.0f;
    sfml->game->player->muzzle_flash_timer = 0.0f;
}

static void apply_minimap_state(sfml_t *sfml, save_data_t *data)
{
    bool should_toggle = false;

    if (data->minimap_active && sfml->game->game_substate != MINI_MAP)
        should_toggle = true;
    else if (!data->minimap_active && sfml->game->game_substate == MINI_MAP)
        should_toggle = true;
    if (should_toggle)
        toggle_mini_map(sfml);
}

static void apply_minimap_zoom(sfml_t *sfml, save_data_t *data)
{
    float target_width;
    float target_height;

    if (!sfml->game->cameras || !sfml->game->cameras->camGame
        || data->minimap_zoom <= 0)
        return;
    target_width = WINDOW_WIDTH * data->minimap_zoom;
    target_height = WINDOW_HEIGHT * data->minimap_zoom;
    sfView_setSize(sfml->game->cameras->camGame,
        (sfVector2f){target_width, target_height});
}

static void need_to_free(sfml_t *sfml, int i)
{
    if (sfml->game->enemies[i]->walk)
        free_sprite_sheet(sfml->game->enemies[i]->walk);
    if (sfml->game->enemies[i]->shoot)
        free_sprite_sheet(sfml->game->enemies[i]->shoot);
    if (sfml->game->enemies[i]->death)
        free_sprite_sheet(sfml->game->enemies[i]->death);
    if (sfml->game->enemies[i]->hurt)
        free_sprite_sheet(sfml->game->enemies[i]->hurt);
}

static void apply_enemies_data(sfml_t *sfml, save_data_t *data)
{
    if (!sfml->game->enemies || data->enemies_count <= 0)
        return;
    for (int i = 0; i < data->enemies_count && i < NUM_ENEMIES; i++) {
        if (sfml->game->enemies[i]) {
            sfml->game->enemies[i]->x = data->enemies[i].x;
            sfml->game->enemies[i]->y = data->enemies[i].y;
            sfml->game->enemies[i]->world_x = data->enemies[i].world_x;
            sfml->game->enemies[i]->world_y = data->enemies[i].world_y;
            sfml->game->enemies[i]->angle = data->enemies[i].angle;
            sfml->game->enemies[i]->hp = data->enemies[i].hp;
            sfml->game->enemies[i]->type = data->enemies[i].type;
            sfml->game->enemies[i]->screen_x = 0;
            sfml->game->enemies[i]->screen_y = 0;
            sfml->game->enemies[i]->distance = 0;
            sfml->game->enemies[i]->scale = 0;
            sfml->game->enemies[i]->visible = 0;
            need_to_free(sfml, i);
            reinit_enemy_sprites(sfml->game->enemies[i]);
        }
    }
}

static void apply_user_settings_data(sfml_t *sfml, save_data_t *data)
{
    if (sfml->menu && sfml->menu->options) {
        sfml->menu->options->music_volume = data->music_volume;
        sfml->menu->options->sfx_volume = data->sfx_volume;
        sfml->menu->options->is_fullscreen = data->is_fullscreen;
        sfml->menu->options->framerate_index = data->framerate_index;
        set_music_volume(sfml, data->music_volume * 10);
        set_sfx_volume(sfml, data->sfx_volume * 10);
    }
    if (sfml->window_size) {
        update_window_size(sfml, data->window_width, data->window_height);
        handle_window_resize(sfml);
    }
}

static void apply_interface_state_data(sfml_t *sfml, save_data_t *data)
{
    float target_width;
    float target_height;

    if (sfml->game->cameras && sfml->game->cameras->camGame) {
        sfView_setCenter(sfml->game->cameras->camGame,
            (sfVector2f){data->camera_center_x, data->camera_center_y});
        if (data->precise_minimap_zoom > 0) {
            target_width = WINDOW_WIDTH * data->precise_minimap_zoom;
            target_height = WINDOW_HEIGHT * data->precise_minimap_zoom;
            sfView_setSize(sfml->game->cameras->camGame,
                (sfVector2f){target_width, target_height});
        }
    }
}

static void validate_player_data(sfml_t *sfml)
{
    if (!sfml->game->player)
        return;
    if (sfml->game->player->hp < 0)
        sfml->game->player->hp = 0;
    if (sfml->game->player->hp > 100)
        sfml->game->player->hp = 100;
    if (sfml->game->player->armor < 0)
        sfml->game->player->armor = 0;
    if (sfml->game->player->armor > 200)
        sfml->game->player->armor = 200;
    if (sfml->game->player->frags < 0)
        sfml->game->player->frags = 0;
    if (sfml->game->player->ammo.bullets < 0)
        sfml->game->player->ammo.bullets = 0;
    if (sfml->game->player->ammo.bullets > 999)
        sfml->game->player->ammo.bullets = 999;
    if (sfml->game->player->ammo.shells < 0)
        sfml->game->player->ammo.shells = 0;
    if (sfml->game->player->ammo.shells > 99)
        sfml->game->player->ammo.shells = 99;
}

void apply_save_data(sfml_t *sfml, save_data_t *data)
{
    if (!sfml || !sfml->game || !data)
        return;
    apply_player_data(sfml, data);
    validate_player_data(sfml);
    memcpy(sfml->game->map, data->map, sizeof(int) * MAP_HEIGHT * MAP_WIDTH);
    apply_minimap_state(sfml, data);
    apply_minimap_zoom(sfml, data);
    apply_enemies_data(sfml, data);
    if (sfml->game->player) {
        sfml->game->player->flashlight_active = data->flashlight_active;
        sfml->game->player->muzzle_flash_timer = data->muzzle_flash_timer;
    }
    apply_user_settings_data(sfml, data);
    apply_interface_state_data(sfml, data);
    if (sfml->clocks)
        restart_clock(sfml);
}
