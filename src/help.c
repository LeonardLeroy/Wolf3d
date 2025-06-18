/*
** EPITECH PROJECT, 2024
** G-ING-210-LYN-2-1-wolf3d-evan.lafolie
** File description:
** help.c
*/

#include "wolf3d.h"

static void print_usage_and_description(void)
{
    printf("WOLF3D - Our Doom Clone\n");
    printf("USAGE:\n");
    printf("    ./wolf3d [OPTIONS]\n\n");
    printf("DESCRIPTION:\n");
    printf("    A 3D first-person shooter using raycasting technique.\n");
    printf("    Navigate through procedurally generated mazes and "
        "experience\n");
    printf("    classic FPS gameplay with modern enhancements.\n\n");
}

static void print_options(void)
{
    printf("OPTIONS:\n");
    printf("    -h,  --help        Display this help message\n");
    printf("    -w,  --width       Set window width (default: 1600, "
        "range: 800-3840)\n");
    printf("    -hg, --height      Set window height (default: 900, "
        "range: 600-2160)\n");
    printf("    -t,  --title       Set window title (default: \"Wolf3d\")\n");
    printf("    -f,  --framerate   Set target framerate (default: 60)\n");
    printf("    -l,  --load        Load game from .json save file\n");
    printf("    -vm, --vol_music   Set music volume (default: 50%%, "
        "range: 0-100)\n");
    printf("    -vs, --vol_sfx     Set SFX volume (default: 50%%, "
        "range: 0-100)\n\n");
}

static void print_controls(void)
{
    printf("CONTROLS:\n  Movement:\n");
    printf("    Z/W/↑        - Move forward\n");
    printf("    S/↓          - Move backward\n");
    printf("    Q/A          - Strafe left\n");
    printf("    D            - Strafe right\n");
    printf("    ←/→          - Turn left/right\n");
    printf("    Mouse        - Look around/Move forward/backward\n");
    printf("    Shift        - Sprint\n\n");
    printf("  Combat:\n");
    printf("    Left Click   - Fire weapon\n");
    printf("    Ctrl         - Fire weapon (alternative)\n");
    printf("    1-5          - Select weapon (Fist/Pistol/Shotgun/Super "
        "Shotgun/Chaingun)\n");
    printf("    Mouse Wheel  - Cycle weapons\n\n");
    printf("  Interface:\n");
    printf("    Tab          - Toggle mini-map\n");
    printf("    Mouse Wheel  - Zoom mini-map (when active)\n");
    printf("    F            - Toggle fullscreen\n");
    printf("    R            - Reset map\n");
    printf("    Esc          - Pause/Menu\n\n");
}

static void print_features(void)
{
    printf("FEATURES:\n");
    printf("  Core Gameplay:\n");
    printf("    ✓ 3D raycasting engine\n");
    printf("    ✓ First-person perspective\n");
    printf("    ✓ Textured walls, floors and ceilings\n");
    printf("    ✓ Collision detection system\n");
    printf("    ✓ Weapon bobbing and camera effects\n\n");
    printf("  Weapons System:\n");
    printf("    ✓ 5 different weapons with unique animations\n");
    printf("    ✓ Particle effects for shots and impacts\n");
    printf("    ✓ Sound effects for each weapon\n");
    printf("    ✓ Frame-rate independent animations\n\n");
    printf("  Visual & Audio:\n");
    printf("    ✓ Animated sprites and textures\n");
    printf("    ✓ Dynamic lighting effects\n");
    printf("    ✓ Particle system for visual effects\n");
    printf("    ✓ Background music and sound effects\n");
    printf("    ✓ Adjustable audio volumes\n\n");
}

static void print_features2(void)
{
    printf("  Interface:\n");
    printf("    ✓ HUD with player information\n");
    printf("    ✓ Interactive mini-map with zoom\n");
    printf("    ✓ Main menu with options\n");
    printf("    ✓ Fullscreen and windowed modes\n");
    printf("    ✓ Customizable settings via command line\n");
    printf("    ✓ Save/Load game functionality\n\n");
    printf("  Technical:\n");
    printf("    ✓ Procedural maze generation\n");
    printf("    ✓ Responsive window resizing\n");
    printf("    ✓ Memory management\n");
    printf("    ✓ Cross-platform compatibility\n");
    printf("    ✓ Configurable framerate and VSync\n\n");
}

static void print_other(void)
{
    printf("MENU NAVIGATION:\n");
    printf("    Arrow Keys   - Navigate menu options\n");
    printf("    Enter/Space  - Select option\n");
    printf("    Mouse        - Click to select\n");
    printf("    Esc          - Go back/Cancel\n\n");
    printf("TECHNICAL INFO:\n");
    printf("    Engine:      Custom raycasting engine\n");
    printf("    Graphics:    SFML\n");
    printf("    Audio:       SFML Audio\n");
    printf("    Save Format: JSON\n");
    printf("    Language:    C\n\n");
}

int print_help(void)
{
    print_usage_and_description();
    print_options();
    print_controls();
    print_features();
    print_features2();
    print_other();
    return 0;
}
