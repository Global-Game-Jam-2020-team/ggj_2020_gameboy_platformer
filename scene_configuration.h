#ifndef SCENE_CONFIGURATION_H
#define SCENE_CONFIGURATION_H

#include <gb/gb.h>
#include <stdio.h>

/*
Misc Assets Sprite table (putting in main.c temporarily)
    MiscAssets.c
        Grave 0-3
            [00][01]
            [02][03]

        Mud Pit (for jumping) 4-11
            [04][05][06][07]
            [08][09][10][11]

        Barricade (for crouching) 12-17
            [12][13][14][15]
            [16][xx][xx][17]
*/

/*
Spirit Friend Ghost Skater (including board) Sprite table (putting in main.c temporarily)
    SpiritSkater.c
        Solid Outline 0-7
            [00][01]
            [02][03]
            [04][05]
            [06][07]

        Thinner / Lighter Outline 8-15
            [08][09]
            [10][11]
            [12][13]
            [14][15]
*/

extern UINT16 completed_loops;
extern UINT16 max_completed_loops;

BOOLEAN scene_collision(UINT8, UINT16, UINT16, UINT16);

// UINT16 _map_width
void scene_initialization(const char *, UINT16);

void scrollable_screen(const char *, UINT16, UINT16);

void scene_core_loop(BOOLEAN scene_is_intro);

void intro_initialization();

// void ghost_friend();
void init_ghost_friend();

#endif