#ifndef PLAYER_H
#define PLAYER_H

#include <gb/gb.h>

struct player
{
    // Is the player currently jumping
    BYTE jumping;

    INT8 gravity;

    UINT8 current_speed_y;
    UINT8 floor_y_position;

    // Will keep track of the player's current position on screen
    UINT16 player_position[2];
};

extern BOOLEAN has_player_been_intialized;

BOOLEAN initialize_player(struct player *);

INT8 would_hit_surface(struct player *, UINT8);

void player_jump(struct player *, UINT8);

// Anything that happens within the player, will occurr in this loop
void player_core_loop(struct player *);

#endif