/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-evan.lafolie
** File description:
** json_wirte.c
*/

#include "wolf3d.h"

static void json_write_player(FILE *file, player_t *player)
{
    fprintf(file, "  \"player\": {\n");
    fprintf(file, "    \"position\": {\"x\": %.2f, \"y\": %.2f},\n",
        player->x, player->y);
    fprintf(file, "    \"angle\": %.4f,\n", player->angle);
    fprintf(file, "    \"momentum\": {\"x\": %.4f, \"y\": %.4f},\n",
        player->momentum_x, player->momentum_y);
    fprintf(file, "    \"health\": %d,\n", player->hp);
    fprintf(file, "    \"armor\": %d,\n", player->armor);
    fprintf(file, "    \"frags\": %d,\n", player->frags);
    fprintf(file, "    \"ammo_normal\": %d,\n", player->ammo.bullets);
    fprintf(file, "    \"ammo_shotgun\": %d,\n", player->ammo.shells);
    fprintf(file, "    \"bob_phase\": %.4f,\n", player->bob_phase);
    fprintf(file, "    \"height_offset\": %.2f\n", player->height_offset);
    fprintf(file, "  }");
}

static void json_write_detail_map(FILE *file, int map[MAP_HEIGHT][MAP_WIDTH],
    int x, int y)
{
    fprintf(file, "%d", map[y][x]);
    if (x < MAP_WIDTH - 1)
        fprintf(file, ",");
}

static void json_write_map(FILE *file, int map[MAP_HEIGHT][MAP_WIDTH])
{
    fprintf(file, "  \"map\": {\n");
    fprintf(file, "    \"width\": %d,\n", MAP_WIDTH);
    fprintf(file, "    \"height\": %d,\n", MAP_HEIGHT);
    fprintf(file, "    \"data\": [\n");
    for (int y = 0; y < MAP_HEIGHT; y++) {
        fprintf(file, "      [");
        for (int x = 0; x < MAP_WIDTH; x++)
            json_write_detail_map(file, map, x, y);
        fprintf(file, "]");
        if (y < MAP_HEIGHT - 1)
            fprintf(file, ",");
        fprintf(file, "\n");
    }
    fprintf(file, "    ]\n");
    fprintf(file, "  }");
}

static void json_write_weapons(FILE *file, weapon_t weapons[WEAPONS_AMOUNT],
    int current)
{
    fprintf(file, "  \"weapons\": {\n");
    fprintf(file, "    \"current_weapon\": \"%s\",\n",
        weapon_type_to_string(current));
    fprintf(file, "    \"weapons_state\": [\n");
    for (int i = 0; i < WEAPONS_AMOUNT; i++) {
        fprintf(file, "      {\n");
        fprintf(file, "        \"type\": \"%s\",\n",
            weapon_type_to_string(weapons[i].type));
        fprintf(file, "        \"shooting\": %s,\n",
            weapons[i].shooting ? "true" : "false");
        fprintf(file, "        \"anim_timer\": %.4f\n",
            weapons[i].sheet->anim_timer);
        fprintf(file, "      }");
        if (i < WEAPONS_AMOUNT - 1)
            fprintf(file, ",");
        fprintf(file, "\n");
    }
    fprintf(file, "    ]\n");
    fprintf(file, "  }");
}

static void json_write_minimap_and_stats(FILE *file, float zoom, int active,
    float play_time)
{
    fprintf(file, "  \"minimap\": {\n");
    fprintf(file, "    \"zoom_level\": %.4f,\n", zoom);
    fprintf(file, "    \"is_active\": %s\n", active ? "true" : "false");
    fprintf(file, "  }");
    fprintf(file, ",\n");
    fprintf(file, "  \"game_stats\": {\n");
    fprintf(file, "    \"play_time\": %.2f\n", play_time);
    fprintf(file, "  }");
}

static void json_write_base_enemy(FILE *file, enemy_t enemies[NUM_ENEMIES],
    int i)
{
    fprintf(file, "      {\n");
    fprintf(file, "        \"x\": %.2f,\n", enemies[i].x);
    fprintf(file, "        \"y\": %.2f,\n", enemies[i].y);
    fprintf(file, "        \"world_x\": %.2f,\n", enemies[i].world_x);
    fprintf(file, "        \"world_y\": %.2f,\n", enemies[i].world_y);
    fprintf(file, "        \"angle\": %.4f,\n", enemies[i].angle);
    fprintf(file, "        \"hp\": %d,\n", enemies[i].hp);
    fprintf(file, "        \"type\": %d,\n", enemies[i].type);
    fprintf(file, "        \"screen_x\": %.2f,\n", enemies[i].screen_x);
    fprintf(file, "        \"screen_y\": %.2f,\n", enemies[i].screen_y);
    fprintf(file, "        \"distance\": %.2f,\n", enemies[i].distance);
    fprintf(file, "        \"scale\": %.4f,\n", enemies[i].scale);
    fprintf(file, "        \"visible\": %s\n", enemies[i].visible ?
        "true" : "false");
    fprintf(file, "      }");
}

static void json_write_enemies(FILE *file, enemy_t enemies[NUM_ENEMIES],
    int count)
{
    fprintf(file, "  \"enemies\": {\n");
    fprintf(file, "    \"count\": %d,\n", count);
    fprintf(file, "    \"data\": [\n");
    for (int i = 0; i < count; i++) {
        json_write_base_enemy(file, enemies, i);
        if (i < count - 1)
            fprintf(file, ",");
        fprintf(file, "\n");
    }
}

static void json_write_visual_effects(FILE *file, save_data_t *save_data)
{
    fprintf(file, "    ]\n");
    fprintf(file, "  }");
    fprintf(file, ",\n");
    fprintf(file, "  \"visual_effects\": {\n");
    fprintf(file, "    \"flashlight_active\": %s,\n",
        save_data->flashlight_active ? "true" : "false");
    fprintf(file, "    \"muzzle_flash_timer\": %.4f\n",
        save_data->muzzle_flash_timer);
    fprintf(file, "  }");
}

static void json_write_user_settings_and_interface_state(FILE *file,
    save_data_t *save_data)
{
    fprintf(file, "  \"user_settings\": {\n");
    fprintf(file, "    \"music_volume\": %d,\n", save_data->music_volume);
    fprintf(file, "    \"sfx_volume\": %d,\n", save_data->sfx_volume);
    fprintf(file, "    \"window_width\": %d,\n", save_data->window_width);
    fprintf(file, "    \"window_height\": %d,\n", save_data->window_height);
    fprintf(file, "    \"is_fullscreen\": %s,\n", save_data->is_fullscreen ?
        "true" : "false");
    fprintf(file, "    \"framerate_index\": %d\n", save_data->framerate_index);
    fprintf(file, "  }");
    fprintf(file, ",\n");
    fprintf(file, "  \"interface_state\": {\n");
    fprintf(file, "    \"camera_center_x\": %.2f,\n",
        save_data->camera_center_x);
    fprintf(file, "    \"camera_center_y\": %.2f,\n",
        save_data->camera_center_y);
    fprintf(file, "    \"precise_minimap_zoom\": %.4f\n",
        save_data->precise_minimap_zoom);
    fprintf(file, "  }");
}

void write_json_to_file(FILE *file, save_data_t *save_data)
{
    fprintf(file, "{\n");
    fprintf(file, " \"version\": \"%s\",\n", save_data->version);
    fprintf(file, " \"timestamp\": \"%s\",\n", save_data->timestamp);
    json_write_player(file, &save_data->player);
    fprintf(file, ",\n");
    json_write_map(file, save_data->map);
    fprintf(file, ",\n");
    json_write_weapons(file, save_data->weapons, save_data->current_weapon);
    fprintf(file, ",\n");
    json_write_minimap_and_stats(file, save_data->minimap_zoom,
        save_data->minimap_active, save_data->play_time);
    fprintf(file, ",\n");
    json_write_enemies(file, save_data->enemies, save_data->enemies_count);
    json_write_visual_effects(file, save_data);
    fprintf(file, ",\n");
    json_write_user_settings_and_interface_state(file, save_data);
    fprintf(file, "\n}\n");
}
