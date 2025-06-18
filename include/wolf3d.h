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
#include <stdbool.h>
#include <dirent.h>

#ifndef WOLF3D_H
    #define WOLF3D_H

    #ifdef _WIN32
        #define MKDIR(path) mkdir(path)
    #else
        #define MKDIR(path) mkdir(path, 0755)
    #endif

    #define PI 3.14159265358979323846

    #define DEFAULT_WINDOW_WIDTH 1600
    #define DEFAULT_WINDOW_HEIGHT 900
    #define DEFAULT_WINDOW_TITLE "Wolf3d"
    #define DEFAULT_FRAMERATE 60
    #define DEFAULT_MAP_SIZE 32
    #define DEFAULT_MUSIC_VOLUME 50
    #define DEFAULT_SFX_VOLUME 50

    #define FULLSCREEN_WIDTH 1920
    #define FULLSCREEN_HEIGHT 1080

    #define MIN_WINDOW_WIDTH 800
    #define MAX_WINDOW_WIDTH 3840
    #define MIN_WINDOW_HEIGHT 600
    #define MAX_WINDOW_HEIGHT 2160
    #define MIN_FRAMERATE 30
    #define MAX_FRAMERATE 240
    #define MIN_VOLUME 0
    #define MAX_VOLUME 100

    #define WINDOW_WIDTH 1600
    #define WINDOW_HEIGHT 900

    #define GAME_TIC 28.571 / 1000
    #define FRAME_DURATION (GAME_TIC * 4)
    #define FINEANGLES 192
    #define FINEMASK (FINEANGLES - 1)
    #define FRACBITS 16
    #define FRACUNIT (1 << FRACBITS)
    #define VIEW_HEIGHT (41 * FRACUNIT)

    #define TILE_SIZE 64
    #define MAP_WIDTH 32
    #define MAP_HEIGHT 32
    #define FOV (PI / 2.5f)
    #define NUM_RAYS 800
    #define PLAYER_HEIGHT 30
    #define NUM_PARTICLES 48

    #define LIGHT_RADIUS 100.0f
    #define LIGHT_CENTER_DISTANCE 80.0f

    #define GRID_SIZE_X 96
    #define GRID_SIZE_Y 96

    #define NUMBER_OF_FRAMERATE 10
    #define NUMBER_OF_VOLUME 11

    #define ROTATION_SPEED 0.0125f
    #define SPRINT_SPEED 7.125f
    #define MOVEMENT_SPEED 0.725f
    #define MOUSE_SENSITIVITY 0.0025f
    #define STRAFE_THRUST 40.0f
    #define FORWARD_THRUST 50.0f

    #define ACCELERATION 0.425f
    #define FRICTION 0.92f
    #define MAX_MOMENTUM 1.8f
    #define MOMENTUM_THRESHOLD 0.02f

    #define MUZZLE_FLASH_DURATION 0.08f
    #define MUZZLE_FLASH_INTENSITY 3.0f
    #define FLASH_CONE (PI / 3.0f)

    #define BOB_SPEED 22.0f
    #define MAX_BOB 0x100000
    #define WEAPON_BOB_SCALE 0.5f

    #define MINI_MAP_MIN_ZOOM_X 640.0f
    #define MINI_MAP_MIN_ZOOM_Y 360.0f
    #define MINI_MAP_MAX_ZOOM_X 1280.0f
    #define MINI_MAP_MAX_ZOOM_Y 720.0f

    #define WALL_TEXTURE "wall"
    #define FLOOR_TEXTURE "floor"
    #define CEILING_TEXTURE "ceiling"

    #define MAX_PATH 64
    #define IMAGE_EXT ".png"
    #define SOUND_EXT ".ogg"

    #define MAX_SOUND_BUFFER 32

    #define WEAPONS_AMOUNT 5

    #define SPACING 150.0f
    #define START_Y 40.0f
    #define LEFT_MARGIN 200.0f
    #define RIGHT_MARGIN 400.0f

    #define SAVE_DIR "saves/"
    #define MAX_FILENAME 64
    #define MAX_FULLPATH 256

    #define TARGET_RATIO 0.40f

    #define CONTROLLER_DEADZONE 30.0f
    #define CONTROLLER_ID 0

    #define NUM_ENEMIES 25
    #define ENEMY_SPEED 1.5f

extern char **menu_sections;
extern char **options_sections;

typedef struct sfml_s sfml_t;

enum GAME_STATE {
    MENU,
    GAME,
    WIN_LOSE
};

enum GAME_SUBSTATE {
    NORMAL,
    MINI_MAP
};

enum MENU_SUBSTATE {
    MAIN,
    OPTIONS,
    SAVES
};

enum WEAPONS {
    FIST,
    PISTOL,
    SHOTGUN,
    SUPER_SHOTGUN,
    CHAINGUN
};

enum ENEMY {
    SOLDIER,
    SHOTGUY,
    IMP
};

typedef enum {
    AI_STATE_DIRECT,
    AI_STATE_WALL_FOLLOW,
    AI_STATE_SEARCH
} ai_state_t;

typedef struct enemy_ai_data_s {
    ai_state_t state;
    float last_player_x;
    float last_player_y;
    float wall_follow_angle;
    int wall_follow_clockwise;
    int stuck_counter;
    int update_frame;
} enemy_ai_data_t;

typedef struct {
    sfSound *sound;
    sfSoundBuffer *buffer;
} sound_player_t;

typedef struct clocks_s {
    sfClock *clock;
    float deltaTime;
    float elapsed;
} clocks_t;

typedef struct sound_handler_s {
    sound_player_t *sound_player[MAX_SOUND_BUFFER];
    int active_sound_count;
    int sfx_volume;
} sound_handler_t;

typedef struct {
    int x, y;
} point_t;

typedef struct {
    point_t *points;
    int size;
    int capacity;
} region_t;

typedef struct wall_sprite_s {
    float x;
    float y;
    int texture_id;
    float distance;
    float angle;
    float size;
    int is_visible;
} wall_sprite_t;

typedef struct wall_sprites_manager_s {
    wall_sprite_t *sprites;
    int count;
    int capacity;
} wall_sprites_manager_t;

typedef struct sprite_s {
    sfSprite *sprite;
    sfTexture *texture;
} sprite_t;

typedef struct sprite_sheet_s {
    sfSprite *sprite;
    sfTexture *texture;
    sfVector2i *offsets;
    float anim_timer;
    int width;
    int height;
    int frames;
    int current_frame;
} sprite_sheet_t;

typedef struct particle_s {
    sprite_sheet_t *sheet;
    int life;
    float size;
    float distance;
    float impact_x;
    float impact_y;
} particle_t;

typedef struct enemy_visibility_s {
    float left_visibility;
    float right_visibility;
    float total_visibility;
    int slice_count;
    int left_slice;
    int right_slice;
} enemy_visibility_t;

typedef struct {
    int start_ray;
    int end_ray;
    int visible_rays;
    float *visibility_mask;
    float total_visibility;
} precise_enemy_visibility_t;

typedef struct enemy_s {
    float x;
    float y;
    float angle;
    int hp;
    float world_x;
    float world_y;
    float screen_x;
    float screen_y;
    float distance;
    float scale;
    int visible;
    enum ENEMY type;
    sprite_sheet_t *walk;
    sprite_sheet_t *shoot;
    sprite_sheet_t *death;
    sprite_sheet_t *hurt;
    sprite_sheet_t *current;
} enemy_t;

typedef struct {
    enemy_t *enemy;
    float distance;
} enemy_depth_t;

typedef struct {
    sfSprite *sprite;
    sfTexture *texture;
    sfFloatRect bounds;
} menu_button_t;

typedef struct texture_s {
    sfTexture *texture;
    sfImage *image;
    int width;
    int height;
} texture_t;

typedef struct fonts_s {
    sfFont *eternal_ui;
    sfFont *doom_ui;
} fonts_t;

typedef struct weapon_s {
    sprite_sheet_t *sheet;
    enum WEAPONS type;
    int shooting;
    float base_x;
    float base_y;
} weapon_t;

typedef struct ammo_s {
    int bullets;
    int shells;
} ammo_t;

typedef struct player_s {
    float x;
    float y;
    float angle;
    float momentum_x;
    float momentum_y;
    float bob_phase;
    float height_offset;
    float weapon_bob_x;
    float weapon_bob_y;
    int hp;
    int armor;
    int frags;
    ammo_t ammo;
    weapon_t *weapon;
    int flashlight_active;
    float muzzle_flash_timer;
    float cos_angle;
    float sin_angle;
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
    sfView *camMenu;
} cameras_t;

typedef struct hud_s {
    sfSprite *stbar;
    sfTexture *stbar_texture;
    sfSprite *doom_guy;
    sfTexture *doom_guy_texture;
    int doomguy_anim_frame;
    float doomguy_anim_clock;
    int doomguy_face_column;
    int doomguy_face_row;
} hud_t;

typedef struct mini_map_s {
    sfRectangleShape *background;
    sfRectangleShape *wall_tile;
    sfSprite *player_marker;
    sfTexture *player_marker_texture;
    sfText *title;
} mini_map_t;

typedef struct bullet_impact_s {
    float hit_x;
    float hit_y;
    float distance;
    int hit_found;
} bullet_impact_t;

typedef struct enemy_ai_manager_s {
    enemy_ai_data_t ai_cache[NUM_ENEMIES];
    int current_frame;
} enemy_ai_manager_t;

typedef struct visibility_cache_s {
    float player_x, player_y, player_angle;
    float enemy_x, enemy_y;
    enemy_visibility_t visibility;
    int frame_calculated;
} visibility_cache_t;

typedef struct visibility_context_s {
    visibility_cache_t cache[NUM_ENEMIES];
    int current_frame;
} visibility_context_t;

typedef struct precise_visibility_cache_s {
    int enemy_id;
    float last_player_x, last_player_y, last_player_angle;
    float last_enemy_x, last_enemy_y;
    precise_enemy_visibility_t cached_visibility;
    int frame_calculated;
} precise_visibility_cache_t;

typedef struct visibility_manager_s {
    precise_visibility_cache_t cache[NUM_ENEMIES];
    int current_frame;
} visibility_manager_t;

typedef struct precise_visibility_manager_s {
    precise_visibility_cache_t visibility_cache[NUM_ENEMIES];
    int current_visibility_frame;
} precise_visibility_manager_t;

typedef struct game_s {
    cameras_t *cameras;
    hud_t *hud;
    player_t *player;
    weapon_t **weapons;
    int map[MAP_HEIGHT][MAP_WIDTH];
    enum GAME_SUBSTATE game_substate;
    mini_map_t *mini_map;
    ray_t *rays;
    texture_t wall_texture;
    texture_t floor_texture;
    texture_t ceiling_texture;
    wall_sprites_manager_t *sprites;
    particle_t **firesparks;
    particle_t **dusts;
    enemy_t **enemies;
    enemy_ai_manager_t *ai_manager;
    visibility_context_t visibility_ctx;
    precise_visibility_manager_t *visibility_manager;
} game_t;

typedef struct config_s {
    unsigned int window_width;
    unsigned int window_height;
    char *window_title;
    unsigned int framerate;
    unsigned int map_width;
    unsigned int map_height;
    char *save_file;
    int music_volume;
    int sfx_volume;
    int use_vsync;
} config_t;

typedef struct char_sprite_s {
    sfSprite *sprite;
    sfTexture *texture;
} char_sprite_t;

typedef struct saves_s {
    menu_button_t *save_button;
    menu_button_t *load_button;
    menu_button_t *back_button;
    menu_button_t *arrow_left;
    menu_button_t *arrow_right;
    char_sprite_t *char_sprites[12];
    sfTexture *save_texture;
    char **save_files;
    int save_count;
    int selected_save_index;
    sfSprite **name_sprites;
    int name_sprites_count;
} saves_t;

typedef struct music_s {
    sfMusic *menu_music;
    sfMusic *music;
    sfMusic *current;
} music_t;

typedef struct options_s {
    menu_button_t *exit;
    menu_button_t *fullscreen_label;
    menu_button_t *fullscreen_yes;
    menu_button_t *fullscreen_no;
    int is_fullscreen;
    menu_button_t *sfx_label;
    menu_button_t *sfx_minus;
    menu_button_t *sfx_plus;
    menu_button_t *sfx_volume_text[NUMBER_OF_VOLUME];
    int sfx_volume;
    menu_button_t *music_label;
    menu_button_t *music_minus;
    menu_button_t *music_plus;
    menu_button_t *music_volume_text[NUMBER_OF_VOLUME];
    int music_volume;
    menu_button_t *framerate_label;
    menu_button_t *framerate_minus;
    menu_button_t *framerate_plus;
    menu_button_t *framerate_text[NUMBER_OF_FRAMERATE];
    int framerate_index;
    menu_button_t *save_button;
    menu_button_t *load_button;
} options_t;

typedef struct menu_s {
    enum MENU_SUBSTATE menu_substate;
    sfTexture *background_texture;
    sfImage *background;
    sfSprite *bg_sprite;
    sfTexture *bg_texture;
    sfSprite *doom_sprite;
    sfTexture *doom_texture;
    options_t *options;
    menu_button_t *start_b;
    menu_button_t *options_b;
    menu_button_t *exit_b;
    menu_button_t *back_b;
    sprite_sheet_t *skull_sheet;
    int game_started;
    int intro;
    saves_t *saves;
} menu_t;

typedef struct win_lose_s {
    int is_win;
    sfSprite *result_sprite;
    sfTexture *result_texture;
    menu_button_t *restart_button;
    menu_button_t *main_menu_button;
    menu_button_t *exit_button;
    float game_time;
    int enemies_killed;
    int remaining_hp;
    float flash_timer;
    float fade_timer;
    sfRectangleShape *flash_overlay;
    sfRectangleShape *fade_overlay;
    int transition_phase;
} win_lose_t;

typedef struct window_size_s {
    unsigned int width;
    unsigned int height;
    float scale_factor_x;
    float scale_factor_y;
} window_size_t;

typedef struct transition_s {
    int active;
    float transition_timer;
    sfSprite **columns;
    int columns_count;
    sfSprite *back;
    sfTexture *back_texture;
    sfSprite *front;
    sfTexture *front_texture;
} transition_t;

typedef struct sfml_s {
    sfRenderWindow *window;
    sfEvent event;
    music_t *music;
    clocks_t *clocks;
    enum GAME_STATE state;
    fonts_t *fonts;
    sprite_t *cursor;
    game_t *game;
    menu_t *menu;
    void (*update_f)(sfml_t *);
    void (*events_f)(sfml_t *);
    sound_handler_t *sound;
    window_size_t *window_size;
    transition_t *transition;
    win_lose_t *win_lose;
} sfml_t;

typedef struct save_data_s {
    char version[16];
    char timestamp[32];
    player_t player;
    int map[MAP_HEIGHT][MAP_WIDTH];
    int current_weapon;
    weapon_t weapons[WEAPONS_AMOUNT];
    float minimap_zoom;
    int minimap_active;
    float play_time;
    enemy_t enemies[NUM_ENEMIES];
    int enemies_count;
    int flashlight_active;
    float muzzle_flash_timer;
    int music_volume;
    int sfx_volume;
    int window_width;
    int window_height;
    int is_fullscreen;
    int framerate_index;
    float camera_center_x;
    float camera_center_y;
    float precise_minimap_zoom;
} save_data_t;

typedef struct {
    int forward_key;
    int strafe_key;
    float is_sprinting;
} input_state_t;

/// CODING STYLE ///

typedef struct relative_pos_s {
    float dx, dy;
    float distance;
    float angle;
} relative_pos_t;

typedef struct display_props_s {
    float screen_x, screen_y;
    float scale;
    float brightness;
} display_props_t;

typedef struct ray_indices_s {
    int left_ray;
    int right_ray;
    int ray_count;
} ray_indices_t;

typedef struct enemy_position_data_s {
    float dx;
    float dy;
    float distance;
    float relative_angle;
} enemy_position_data_t;

typedef struct sprite_properties_s {
    sfIntRect original_rect;
    sfVector2f original_pos;
    sfVector2f scale;
} sprite_properties_t;

typedef struct visibility_points_s {
    int left_visible;
    int center_visible;
    int right_visible;
    float visible_parts;
} visibility_points_t;

typedef struct layout_info_s {
    float scale;
    float char_width;
    float save_width;
    float start_x;
    float y;
} layout_info_t;

typedef struct switch_state_args_s {
    enum GAME_STATE state;
    void (*update)(sfml_t *);
    void (*events)(sfml_t *);
} switch_state_args_t;

typedef struct switch_menu_substate_args_s {
    enum MENU_SUBSTATE substate;
    void (*update)(sfml_t *);
    void (*events)(sfml_t *);
} switch_menu_substate_args_t;
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

typedef struct sprite_params_s {
    float x;
    float y;
    int texture_id;
    float size;
} sprite_params_t;

typedef struct player_movement_s {
    float current_speed;
    float acceleration;
    int forward_key;
    int strafe_key;
} player_movement_t;

typedef struct floor_render_params_s {
    sfml_t *sfml;
    float ray_dir_x0;
    float ray_dir_y0;
    float ray_dir_x1;
    float ray_dir_y1;
    float player_height;
    float tile_world_size;
    int block_size;
    sfVector2u window_size;
    texture_t *floor_texture;
    sfRenderWindow *window;
    player_t *player;
} floor_render_params_t;

typedef struct floor_row_data_s {
    float row_distance;
    float floor_step_x;
    float floor_step_y;
    float floor_x_start;
    float floor_y_start;
    float brightness;
} floor_row_data_t;

typedef struct menu_layout_params_s {
    options_t *opt;
    float scale;
    float left_margin;
    float right_margin;
    float minus_x;
    float start_y;
    float spacing;
    sfVector2u window_size;
} menu_layout_params_t;

typedef struct triangle_params_s {
    float brightness;
    float next_brightness;
    float ray_angle;
    float next_ray_angle;
    float row_distance;
    float next_row_distance;
    sfVertexArray *vertices;
    int x;
    int y;
} triangle_params_t;

typedef struct vect_s {
    float ray_dir_x1;
    float ray_dir_y1;
    float ray_dir_x2;
    float ray_dir_y2;
    float screen_x1;
    float screen_x2;
    float row_distance1_f;
    float row_distance2_f;
    float row_brightness1_f;
    float row_brightness2_f;
    float screen_y1_f;
    float screen_y2_f;
    float row_distance1_c;
    float row_distance2_c;
    float row_brightness1_c;
    float row_brightness2_c;
    float screen_y1_c;
    float screen_y2_c;
} vect_t;

typedef struct fetch_vect_params_s {
    float ray_dir_x;
    float ray_dir_y;
    float row_dist;
    float row_brightness;
    float screen_x;
    float screen_y;
} fetch_vect_params_t;

typedef struct cos_sin_s {
    sfVector2f cos;
    sfVector2f sin;
} cos_sin_t;

typedef struct row_properties_params_s {
    float y;
    float horizon;
    float window_height;
    float tan_fov_half;
    float player_height_times_half;
} row_properties_params_t;

typedef struct volume_controls_params_s {
    menu_button_t **label;
    menu_button_t **minus;
    menu_button_t **plus;
    menu_button_t **volume_text;
    const char *label_name;
    float y_position;
    int *volume_value;
    float left_margin;
    float right_margin;
} volume_controls_params_t;

typedef struct flood_fill_context_s {
    sfml_t *sfml;
    int visited[MAP_HEIGHT][MAP_WIDTH];
    region_t **regions;
    int *region_count;
    point_t *stack;
    int *stack_size;
} flood_fill_context_t;

typedef struct wall_check_args_s {
    float current_x;
    float current_y;
    float dx;
    float dy;
} wall_check_args_t;

typedef struct line_s {
    float x1;
    float y1;
    float x2;
    float y2;
} line_t;

typedef struct enemy_distance_s {
    enemy_t *enemy;
    int index;
    float distance;
} enemy_distance_t;

typedef struct enemy_params_s {
    sfVector2i frame_size;
    char *name;
} enemy_params_t;

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
void draw_game(sfml_t *sfml);
void update(sfml_t *sfml);
void game_over(sfml_t *sfml);
void free_sfml(sfml_t *sfml);

/// WINDOW ///
void init_window(sfml_t *sfml);
void free_window(sfml_t *sfml);

void init_cursor(sfml_t *sfml);
void update_mouse(sfml_t *sfml);
void free_cursor(sfml_t *sfml);

/// FONTS ///
void init_fonts(sfml_t *sfml);
void free_fonts(sfml_t *sfml);

/// GAME ///
void init_game(sfml_t *sfml);
void game_events(sfml_t *sfml);
void reset_game(sfml_t *sfml);
void update_game(sfml_t *sfml);
void free_game(sfml_t *sfml);
void init_rays(ray_t *ray);

/// CAMERS ///
void init_cameras(sfml_t *sfml);
void free_cameras(sfml_t *sfml);

/// CLOCK ///
void init_clock(sfml_t *sfml);
void update_clock(sfml_t *sfml);
void restart_clock(sfml_t *sfml);
void free_clock(sfml_t *sfml);

/// HUD ///
void init_hud(sfml_t *sfml);
void free_hud(sfml_t *sfml);
void update_hud(sfml_t *sfml);
void regular_doom_face(sfml_t *sfml);
int check_doomguy_sprite_row(sfml_t *sfml);
sfVector2f get_stbar_position(sfRenderWindow *window,
    sfTexture *texture, float scale);
void set_doomguy_face(sfml_t *sfml, int column);
void draw_hud(sfml_t *sfml);

/// MUSIC ///
void init_music(sfml_t *sfml);
void change_music(sfml_t *sfml, sfMusic *music);
void free_music(sfml_t *sfml);

/// PLAYER ///
void init_player(sfml_t *sfml);
void free_player(sfml_t *sfml);
void update_player(sfml_t *sfml);
int will_collide_with_wall(sfml_t *sfml, float new_x, float new_y);
void handle_stop_firing_requested(sfml_t *sfml,
    int *stop_firing_requested);
void update_player_movement(sfml_t *sfml, float dt_factor);
void update_camera_bob(sfml_t *sfml, float dt_factor);
void move_player(sfml_t *sfml, float speed, float angle);

/// MAP ///
void init_map(sfml_t *sfml, FILE *file);
void open_map(sfml_t *sfml, char *filename);
void generate_procedural_map(sfml_t *sfml);
void connect_regions(sfml_t *sfml, region_t **regions, int region_count);
void add_point_to_region(region_t *region, int x, int y);
void free_regions(region_t **regions, int region_count);
region_t *create_region(void);
void create_tunnel(sfml_t *sfml, point_t from, point_t to);
region_t **find_all_regions(sfml_t *sfml, int *region_count);
void adjust_density(sfml_t *sfml);
int count_wall_neighbors(sfml_t *sfml, int x, int y, int radius);

/// MINI MAP ///
void init_mini_map(sfml_t *sfml);
void free_mini_map(sfml_t *sfml);
void mini_map_zoom(sfml_t *sfml);
void mini_map_zoom_controller(sfml_t *sfml);
void render_mini_map(sfml_t *sfml);
void draw_wall_sides(sfml_t *sfml, int x, int y);
void toggle_mini_map(sfml_t *sfml);

/// RESPONSIVE ///
void init_window_size(sfml_t *sfml);
void handle_window_resize(sfml_t *sfml);
void free_window_size(sfml_t *sfml);
float get_scale_factor(sfml_t *sfml);
float get_x_weapon_offset(enum WEAPONS type);
float get_y_weapon_offset(enum WEAPONS type);
sfVector2f calculate_weapon_position(sfml_t *sfml, weapon_t *weapon);
void update_menu_background(sfml_t *sfml);
void update_window_size(sfml_t *sfml, unsigned int new_width,
    unsigned int new_height);
void update_options_menu_positions(sfml_t *sfml);
void update_main_menu_positions(sfml_t *sfml);

/// MENUS ///
void init_menu(sfml_t *sfml);
menu_button_t *create_menu_button(sfml_t *sfml, char const *texture_path,
    int n);
sfSprite *create_color_sprite(unsigned int width, unsigned height,
    sfColor color);
void update_menu(sfml_t *sfml);
void events_menu(sfml_t *sfml);
void free_menu(sfml_t *sfml);
void render_color(sfml_t *sfml);
void init_options(sfml_t *sfml);
void update_options(sfml_t *sfml);
void events_options(sfml_t *sfml);
void update_options(sfml_t *sfml);
void free_options(sfml_t *sfml);
void set_sfx_volume(sfml_t *sfml, int volume);
void set_music_volume(sfml_t *sfml, int volume);
void toggle_fullscreen(sfml_t *sfml);
void position_plus_button(menu_button_t *percentage,
    menu_button_t *plus_button);
void update_sfx_options(const menu_layout_params_t *params);
void update_music_options(const menu_layout_params_t *params);
void init_volume_options(sfml_t *sfml);
void config_menu_button(menu_button_t *button, float scale, float pos_x,
    float pos_y);
menu_button_t *create_button_with_scale(char const *texture_path, float scale);
void init_saves(sfml_t *sfml);
void update_saves(sfml_t *sfml);
void events_saves(sfml_t *sfml);
void free_saves(sfml_t *sfml);
void create_name_sprites(sfml_t *sfml, saves_t *saves);
void position_arrows(sfml_t *sfml, saves_t *saves);
void load_saves_list(saves_t *saves);
void update_saves_menu_positions(sfml_t *sfml);

/// FLASHLIGHT ///
void toggle_flashlight(sfml_t *sfml);
int is_in_flashlight_cone(sfml_t *sfml, float world_x, float world_y);
float apply_flashlight(sfml_t *sfml, float world_x,
    float world_y, float original_brightness);
void trigger_muzzle_flash(sfml_t *sfml);
void trigger_muzzle_flash_repetitive(sfml_t *sfml, float intensity);
int can_trigger_new_flash(sfml_t *sfml);

/// RAY CASTING ///
void cast_ray(sfml_t *sfml, float ray_angle, int ray_id);
void cast_all_rays(sfml_t *sfml);
void calculate_wall_hit(sfml_t *sfml, float ray_angle, int ray_id);
void adjust_for_ray_direction(float ray_angle, float next_coord,
    float *check_coord, int is_x_axis);
void render_surfaces(sfml_t *sfml);
void load_textures(sfml_t *sfml);
void free_textures(sfml_t *sfml);
float calculate_horizontal_distance(sfml_t *sfml, float ray_angle);
void calculate_wall_hit_from_horizontal(sfml_t *sfml, float ray_angle,
    int ray_id);
float calculate_vertical_distance(sfml_t *sfml, float ray_angle);
void calculate_wall_hit_from_vertical(sfml_t *sfml, float ray_angle,
    int ray_id);
void render_textured_floor(sfml_t *sfml);
void add_triangle(triangle_params_t params, sfml_t *sfml);
void calculate_camera_vectors(sfml_t *sfml, sfVector2f *cos,
    sfVector2f *sin);
sfVertexArray *create_vertex_array(void);
void calculate_ray_angle(triangle_params_t *params, unsigned int x,
    sfVector2u window_size, float player_angle);
void draw_vertices(sfVertexArray *ceiling_vertices,
    sfVertexArray *floor_vertices, sfml_t *sfml, vect_t *vec);

/// SPRITES ///
void init_sprites(sfml_t *sfml);
void free_sprites(sfml_t *sfml);
void add_sprite(sfml_t *sfml, sprite_params_t params);
void update_sprites(sfml_t *sfml);
void sort_sprites_by_distance(sfml_t *sfml);
void find_visible_sprites(sfml_t *sfml);
void render_sprites(sfml_t *sfml);
sprite_sheet_t *create_sprite_sheet(char const *img, int width,
    int height, int frames);
void set_current_frame(sprite_sheet_t *sheet, int frame);
void update_skull(sfml_t *sfml, sprite_sheet_t *sheet);
void free_sprite_sheet(sprite_sheet_t *sheet);

/// CONFIG ///
config_t *init_default_config(void);
void destroy_config(config_t *config);
int parse_args(int argc, char **argv, config_t *config);
int print_help(void);
void validate_config(config_t *config);

/// WEAPONS ///
void init_weapons(sfml_t *sfml);
void handle_shooting(sfml_t *sfml);
void handle_release_shooting(sfml_t *sfml,
    int *stop_firing_requested);
void switch_weapon(sfml_t *sfml, int direction);
void draw_weapon(sfml_t *sfml);
void play_weapon_sound(sfml_t *sfml, enum WEAPONS weapon);
void update_weapon(sfml_t *sfml, weapon_t *weapon);
int handle_special_weapons(sfml_t *sfml, weapon_t *weapon);
int handle_ammo_by_type(player_t *player, int weapon_type);
void free_weapons(sfml_t *sfml);
int handle_ammo(player_t *player, weapon_t *weapon);

/// PARTICLES ///
void init_particles(sfml_t *sfml);
void play_weapon_particle(sfml_t *sfml, int id);
void play_particle(sfml_t *sfml, particle_t *particle);
void reset_particle(particle_t *particle);
void update_particles(sfml_t *sfml);
void free_particles(sfml_t *sfml);
void update_particle_position(sfml_t *sfml, particle_t *particle);
bullet_impact_t calculate_bullet_impact(sfml_t *sfml, int id);
void play_particle_at_impact(sfml_t *sfml, particle_t *particle,
    bullet_impact_t impact);
void draw_particles(sfml_t *sfml);

/// ENEMIES ///
void init_enemies(sfml_t *sfml);
float calculate_direction_to_player(sfml_t *sfml, enemy_t *enemy);
int is_position_free(sfml_t *sfml, float x, float y);
void update_enemy_position(enemy_t *enemy, float new_x, float new_y);
int try_direct_movement(sfml_t *sfml, enemy_t *enemy, int enemy_id,
    enemy_ai_manager_t *ai_mgr);
float get_dir(int index);
void move_towards_player(sfml_t *sfml, enemy_t *enemy, int enemy_id,
    enemy_ai_manager_t *ai_mgr);
void perform_enemy_ia(sfml_t *sfml, enemy_t *enemy, int enemy_id,
    enemy_ai_manager_t *ai_mgr);
int will_collide_with_enemy(sfml_t *sfml, float new_x, float new_y);
void update_enemies(sfml_t *sfml, enemy_ai_manager_t *ai_mgr);
void cleanup_enemy_pathfinding(enemy_ai_manager_t *ai_mgr);
void update_enemy_anims(enemy_t *enemy);
void enemy_grunt(sfml_t *sfml, enemy_t *enemy);
void hurt_enemy(sfml_t *sfml, enemy_t *enemy);
void handle_enemy_attack(sfml_t *sfml, enemy_t *enemy);
void draw_enemies(sfml_t *sfml);
void free_enemies(sfml_t *sfml);
void attack_player(sfml_t *sfml, enemy_t *enemy);
float calculate_enemy_visibility_percentage(sfml_t *sfml, enemy_t *enemy);
int has_clear_line_of_sight(sfml_t *sfml, line_t line);
int is_enemy_visible_with_walls(sfml_t *sfml, enemy_t *enemy);
sfVector2i get_enemy_frame_size(enum ENEMY type);
int is_point_visible(sfml_t *sfml, float x, float y);
void handle_enemy_death(enemy_t *enemy);
void update_visibility_frame(sfml_t *sfml);
float calculate_enemy_distance(enemy_t *enemy, player_t *player);
enemy_ai_manager_t *init_enemy_pathfinding(void);
void update_pathfinding_frame(enemy_ai_manager_t *ai_mgr);
enemy_visibility_t get_enemy_visibility(sfml_t *sfml, enemy_t *enemy,
    int enemy_id);
precise_enemy_visibility_t calculate_precise_enemy_visibility(sfml_t *sfml,
    enemy_t *enemy);
void draw_enemies_with_precise_occlusion(sfml_t *sfml);
void cleanup_precise_visibility_cache(precise_visibility_manager_t *vis_mgn);
precise_visibility_manager_t *init_precise_visibility_manager(void);
relative_pos_t calculate_relative_position(player_t *player,
    enemy_t *enemy);
int check_basic_visibility(relative_pos_t pos);
int check_line_of_sight(sfml_t *sfml, player_t *player, enemy_t *enemy);
display_props_t calculate_display_properties(sfml_t *sfml,
    enemy_t *enemy, relative_pos_t pos);
int check_line_of_sight(sfml_t *sfml, player_t *player, enemy_t *enemy);

/// TOOLS ///
int print_help(void);
void *salloc(size_t size);
char *my_strcat(char const *text1, char const *text2);
void cat(char *dest, const char *src);
float normalize_angle(float angle);
float normalize_angle_range(float angle);
void init_sounds(sfml_t *sfml);
void free_sounds(sfml_t *sfml);
void play_sound(sfml_t *sfml, const char *snd, int vol);
void sound_update(sfml_t *sfml);
void destroy_sounds(sfml_t *sfml);
void change_bg_sprite(sfml_t *sfml);
void recenter_mouse(sfml_t *sfml);
float get_centered_x(sfml_t *sfml, sfSprite *sprite);
float get_centered_y(sfml_t *sfml, sfSprite *sprite);
void switch_state(sfml_t *sfml, switch_state_args_t args);
void switch_menu_substate(sfml_t *sfml, switch_menu_substate_args_t args);

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
sfVertex fetch_vect(sfml_t *sfml, fetch_vect_params_t params);
void find_enemy_position(sfml_t *sfml, enemy_t *enemy);

void render_floor_ceiling(sfml_t *sfml);

/// CONTROLLER ///
void handle_controller_inputs(sfml_t *sfml,
    int *weapon_switch_requested);
void get_controller_input(input_state_t *input);

/// SAVE/LOAD GAME ///
int save_game(sfml_t *sfml);
int list_saves_and_load_latest(sfml_t *sfml);
float parse_float_value(const char *json, const char *key);
int parse_int_value(const char *json, const char *key);
void parse_string_value(const char *json, const char *key, char *output,
    int max_len);
void parse_map_data(const char *json, int map[MAP_HEIGHT][MAP_WIDTH]);
int parse_bool_value(const char *json, const char *key);
void write_json_to_file(FILE *file, save_data_t *save_data);
char **list_save_files(int *count);
void apply_save_data(sfml_t *sfml, save_data_t *data);
int parse_json_file(const char *filename, save_data_t *data);
void cleanup_name_sprites(saves_t *saves);
const char *weapon_type_to_string(enum WEAPONS type);
char *parse_float_field(const char *json_section, char *start_pos,
    const char *field_name, float *value);
char *parse_int_field(const char *json_section, char *start_pos,
    const char *field_name, int *value);
void reinit_enemy_sprites(enemy_t *enemy);
void parse_enemies_data(const char *json, save_data_t *data);
char *read_json_file(const char *filename);
void parse_player_data(const char *json_content, save_data_t *data);

/// TRANSITION ///
void init_transition(sfml_t *sfml);
int handle_transition(sfml_t *sfml);
void handle_transition_state(sfml_t *sfml);
void free_transition(sfml_t *sfml);

/// WIN/LOSE MENU ///
void init_win_lose(sfml_t *sfml);
void update_win_lose(sfml_t *sfml);
void events_win_lose(sfml_t *sfml);
void free_win_lose(sfml_t *sfml);
void trigger_game_win(sfml_t *sfml);
void trigger_game_lose(sfml_t *sfml);
void update_win_lose_positions(sfml_t *sfml);
void update_win_lose_buttons_positions(sfml_t *sfml);

#endif
