/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** wolf3d.h
*/

#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <SFML/Audio.h>

#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>

#ifndef WOLF3D_H
    #define WOLF3D_H

    #define PI 3.14159265358979323846

    #define WINDOW_WIDTH 1280
    #define WINDOW_HEIGHT 720

    #define TILE_SIZE 64
    #define MAP_WIDTH 8
    #define MAP_HEIGHT 8
    #define FOV (PI / 2)
    #define NUM_RAYS 600
    #define PLAYER_HEIGHT 30

    #define ROTATION_SPEED 0.0125f
    #define SPRINT_SPEED 0.9f
    #define MOVEMENT_SPEED 0.5f
    #define MOUSE_SENSITIVITY 0.0025f

    #define MAX_PATH 32
    #define IMAGE_EXT ".png"
    #define SOUND_EXT ".ogg"

typedef struct player_s {
    float x;
    float y;
    float angle;
} player_t;

typedef struct ray_data_s {
    float xintercept;
    float yintercept;
    float xstep;
    float ystep;
    float next_x;
    float next_y;
} ray_data_t;

typedef struct ray_s {
    float angle;
    float wall_hit_x;
    float wall_hit_y;
    float distance;
    int was_hit_vertical;
    int wall_hit_content;
} ray_t;

typedef struct cameras_s {
    sfView *camGame;
    sfView *camHUD;
} cameras_t;

typedef struct hud_s {
    sfTexture *stbar_texture;
    sfSprite *stbar;
    sfTexture *doom_guy_texture;
    sfSprite *doom_guy;
} hud_t;

typedef struct game_s {
    cameras_t *cameras;
    hud_t *hud;
    player_t *player;
    int map[MAP_HEIGHT][MAP_WIDTH];
    ray_t *rays;
} game_t;

typedef struct sfml_s {
    sfRenderWindow *window;
    sfEvent event;
    sfMusic *music;
    sfClock *clock;
    game_t *game;
} sfml_t;

/// CODING STYLE ///
typedef struct {
    int index;
    float strip_width;
    float height;
    float top_pixel;
} wall_strip_params_t;

typedef struct collision_check_s {
    float check_x;
    float check_y;
    float next_x;
    float next_y;
} collision_check_t;

typedef struct wall_hit_data_s {
    float ray_angle;
    int ray_id;
    float horz_dist;
    float vert_dist;
} wall_hit_data_t;
/// CODING STYLE ///

/// PATHS ///
char *image(char const *img);
char *font(char const *font);
char *file(char const *text, char const *format);
char *sound(char const *snd);
char *music(char const *msc);

/// SFML ///
void init_sfml(sfml_t *sfml);
void events(sfml_t *sfml);
void draw(sfml_t *sfml);
void update(sfml_t *sfml);
void free_sfml(sfml_t *sfml);

/// WINDOW ///
void init_window(sfml_t *sfml);
void free_window(sfml_t *sfml);

/// GAME ///
void init_game(sfml_t *sfml);
void free_game(sfml_t *sfml);
void init_rays(ray_t *ray);

/// CAMERS ///
void init_cameras(sfml_t *sfml);
void free_cameras(sfml_t *sfml);

/// CLOCK ///
void init_clock(sfml_t *sfml);
void restart_clock(sfml_t *sfml);
void free_clock(sfml_t *sfml);

/// HUD ///
void init_hud(sfml_t *sfml);
void free_hud(sfml_t *sfml);

/// MUSIC ///
void init_music(sfml_t *sfml);
void play_music(sfml_t *sfml);
void change_music(sfml_t *sfml);
void pause_music(sfml_t *sfml);
void free_music(sfml_t *sfml);

/// PLAYER ///
void init_player(sfml_t *sfml);
void free_player(sfml_t *sfml);
void update_player(sfml_t *sfml);
void move_player(sfml_t *sfml, float speed, float angle);

/// MAP ///
void init_map(sfml_t *sfml);
void determine_map_content(sfml_t *sfml, int i, int j);
void reset_map(sfml_t *sfml);
void draw_floor_and_ceiling(sfml_t *sfml);

/// RAY CASTING ///
void cast_ray(sfml_t *sfml, float ray_angle, int ray_id);
void cast_all_rays(sfml_t *sfml);
void calculate_wall_hit(sfml_t *sfml, float ray_angle, int ray_id);
void adjust_for_ray_direction(float ray_angle, float next_coord,
    float *check_coord, int is_x_axis);
void render_ceiling(sfml_t *sfml);
void render_floor(sfml_t *sfml);
void render_walls(sfml_t *sfml);
float calculate_horizontal_distance(sfml_t *sfml, float ray_angle);
void calculate_wall_hit_from_horizontal(sfml_t *sfml, float ray_angle,
    int ray_id);
float calculate_vertical_distance(sfml_t *sfml, float ray_angle);
void calculate_wall_hit_from_vertical(sfml_t *sfml, float ray_angle,
    int ray_id);

/// TOOLS ///
void *salloc(size_t size);
void cat(char *dest, const char *src);
float normalize_angle(float angle);

int is_wall(sfml_t *sfml, float x, float y);
int is_within_bounds(float next_x, float next_y);
int is_ray_facing_up(float angle);
int is_ray_facing_down(float angle);
int is_ray_facing_left(float angle);
int is_ray_facing_right(float angle);
void init_next_coordinates(float xintercept, float yintercept,
    float *next_x, float *next_y);
float calculate_actual_distance(float x1, float y1, float x2, float y2);
int check_wall_hit(sfml_t *sfml, collision_check_t check, int ray_id);
#endif
