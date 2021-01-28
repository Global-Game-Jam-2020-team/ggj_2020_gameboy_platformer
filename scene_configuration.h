#ifndef SCENE_CONFIGURATION_H
#define SCENE_CONFIGURATION_H

#include <gb/gb.h>
#include <stdio.h>

BOOLEAN scene_collision(UINT8, UINT16, UINT16, UINT16);

BOOLEAN scene_initialization(const char *, UINT16, UINT16);

// GOAL: We are gonna need to keep track of the player
// and only move the background when they are halfway on the screen x pos
void scene_core_loop();

#endif