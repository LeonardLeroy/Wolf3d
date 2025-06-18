/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** update_player.c
*/

#include "wolf3d.h"

static float calculate_distance(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;

    return sqrt(dx * dx + dy * dy);
}

int check_enemy_collision(enemy_t *enemy, player_t *player,
    float new_x, float new_y)
{
    float distance_current;
    float distance_new;

    if (enemy->hp <= 0)
        return 0;
    if (!(fabs(enemy->world_x - player->x) <= 100.0f &&
        fabs(enemy->world_y - player->y) <= 100.0f))
        return 0;
    distance_current = calculate_distance(enemy->world_x,
        enemy->world_y, player->x, player->y);
    distance_new = calculate_distance(enemy->world_x,
        enemy->world_y, new_x, new_y);
    if ((distance_current > 25.0f && distance_new > 25.0f) ||
        distance_new >= distance_current - 0.1f)
        return 0;
    if (!((new_x - player->x) * (enemy->world_x - player->x) +
    (new_y - player->y)
        * (enemy->world_y - player->y) > 0))
        return 0;
    return (distance_new <= 20.0f);
}

int will_collide_with_enemy(sfml_t *sfml, float new_x, float new_y)
{
    player_t *player = sfml->game->player;

    if (!sfml->game->enemies)
        return 0;
    for (int i = 0; i < NUM_ENEMIES; i++) {
        if (check_enemy_collision(sfml->game->enemies[i],
            player, new_x, new_y))
            return 1;
    }
    return 0;
}

static void apply_momentum(sfml_t *sfml, float dt_factor)
{
    player_t *player = sfml->game->player;
    float new_x = player->x + player->momentum_x * dt_factor;
    float new_y = player->y + player->momentum_y * dt_factor;

    if (!will_collide_with_wall(sfml, new_x, player->y) &&
        !will_collide_with_enemy(sfml, new_x, player->y))
        player->x = new_x;
    else
        player->momentum_x = 0;
    if (!will_collide_with_wall(sfml, player->x, new_y) &&
        !will_collide_with_enemy(sfml, player->x, new_y))
        player->y = new_y;
    else
        player->momentum_y = 0;
    player->momentum_x *= powf(FRICTION, dt_factor);
    player->momentum_y *= powf(FRICTION, dt_factor);
    if (fabsf(player->momentum_x) < MOMENTUM_THRESHOLD)
        player->momentum_x = 0;
    if (fabsf(player->momentum_y) < MOMENTUM_THRESHOLD)
        player->momentum_y = 0;
}

static int keyboard_movement(void)
{
    if (sfKeyboard_isKeyPressed(sfKeyZ)
        || sfKeyboard_isKeyPressed(sfKeyUp)
        || sfKeyboard_isKeyPressed(sfKeyS)
        || sfKeyboard_isKeyPressed(sfKeyDown)
        || sfKeyboard_isKeyPressed(sfKeyQ)
        || sfKeyboard_isKeyPressed(sfKeyD))
        return 1;
    return 0;
}

static void handle_mouse_movement(sfml_t *sfml)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(sfml->window);
    sfVector2u window_size = sfRenderWindow_getSize(sfml->window);
    int center_x = window_size.x / 2;
    int center_y = window_size.y / 2;
    player_t *player = sfml->game->player;
    float mvt;

    if (mouse_pos.x != center_x) {
        player->angle += (mouse_pos.x - center_x) * MOUSE_SENSITIVITY;
        player->angle = normalize_angle(sfml->game->player->angle);
    }
    if (mouse_pos.y != center_y && !keyboard_movement()) {
        mvt = (center_y - mouse_pos.y) * MOUSE_SENSITIVITY * 10;
        player->momentum_x += cos(sfml->game->player->angle) * mvt;
        player->momentum_y += sin(sfml->game->player->angle) * mvt;
    }
    sfMouse_setPositionRenderWindow((sfVector2i){center_x, center_y},
        sfml->window);
}

static void update_player_rotation_controller(sfml_t *sfml)
{
    float joy_x = sfJoystick_getAxisPosition(CONTROLLER_ID, sfJoystickU);

    if (fabs(joy_x) > CONTROLLER_DEADZONE) {
        if (joy_x < - CONTROLLER_DEADZONE)
            sfml->game->player->angle -= ROTATION_SPEED * 1.4f;
        if (joy_x > CONTROLLER_DEADZONE)
            sfml->game->player->angle += ROTATION_SPEED * 1.4f;
        sfml->game->player->angle = normalize_angle(sfml->game->player->angle);
    }
}

static void update_player_rotation(sfml_t *sfml)
{
    if (sfKeyboard_isKeyPressed(sfKeyLeft)) {
        sfml->game->player->angle -= ROTATION_SPEED;
        sfml->game->player->angle = normalize_angle(sfml->game->player->angle);
    }
    if (sfKeyboard_isKeyPressed(sfKeyRight)) {
        sfml->game->player->angle += ROTATION_SPEED;
        sfml->game->player->angle = normalize_angle(sfml->game->player->angle);
    }
    handle_mouse_movement(sfml);
}

void update_player(sfml_t *sfml)
{
    float dt_factor = sfml->clocks->deltaTime * 60.0f;

    if (dt_factor > 5.0f)
        dt_factor = 5.0f;
    if (sfml->game->player->muzzle_flash_timer > 0.0f) {
        sfml->game->player->muzzle_flash_timer -= sfml->clocks->deltaTime;
        if (sfml->game->player->muzzle_flash_timer < 0.0f)
            sfml->game->player->muzzle_flash_timer = 0.0f;
    }
    if (sfJoystick_isConnected(CONTROLLER_ID))
        update_player_rotation_controller(sfml);
    update_player_rotation(sfml);
    update_player_movement(sfml, dt_factor);
    apply_momentum(sfml, dt_factor);
    update_camera_bob(sfml, dt_factor);
}
