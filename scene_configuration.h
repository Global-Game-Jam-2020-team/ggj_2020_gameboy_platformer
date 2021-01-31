#ifndef SCENE_CONFIGURATION_H
#define SCENE_CONFIGURATION_H

#include <gb/gb.h>
#include <stdio.h>

BOOLEAN scene_collision(UINT8, UINT16, UINT16, UINT16);

// UINT16 _map_width
void scene_initialization(const char *, UINT16);

void scrollable_screen(const char *, UINT16, UINT16);

void scene_core_loop();

#endif