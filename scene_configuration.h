#ifndef SCENE_CONFIGURATION_H
#define SCENE_CONFIGURATION_H

#include <gb/gb.h>
#include <stdio.h>

BOOLEAN scene_collision(UINT8, UINT16, UINT16, UINT16);

BOOLEAN scene_initialization(const char *, UINT16, UINT16);

// Will take the current background map, and slowly pan it while switching to the new one.
// Take in a direction in which the player wants to go and the two maps.
void scene_transition(const char*, UINT8, UINT8);

void scrollable_screen(const char*, UINT16, UINT16);

void scene_core_loop();

#endif