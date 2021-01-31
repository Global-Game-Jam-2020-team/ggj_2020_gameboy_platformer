#ifndef PLAYER_H
#define PLAYER_H

#include <gb/gb.h>

/*
Skater sprites table:
    Skater.c
        standing 0-5
            [00][01]
            [02][03]
            [04][05]

        skateboard 6-7
            [06]
            [07]

        crouching: 8-13
            [08][09]
            [10][11]
            [12][13]
        
        jumping 14-19
            [14][15]
            [16][17]
            [18][19]

        skateboard while jumping 20
            [20]

        backside looking at grave 21-26
            [21][22]
            [23][24]
            [25][26]
*/

struct player
{
    // Is the player currently jumping
    BYTE jumping;

    INT8 gravity;

    UINT8 current_speed_y;
    UINT8 floor_y_position;

    UINT16 index_top_left_x;
    UINT16 index_top_left_y;
    UINT16 tile_index_top_left;

    // Will keep track of the player's current position on screen
    UINT16 player_position[2];
};

extern BOOLEAN has_player_been_intialized;

BOOLEAN initialize_player(struct player *);

INT8 would_hit_surface(struct player *, UINT8);

void player_jump(struct player *, UINT8);

void player_movement(struct player *);

void update_Player(struct player *);

// Anything that happens within the player, will occurr in this loop
void player_core_loop(struct player *);

// Only if the player is not jumping, we are gonna check the ground,
// If there is no floor, pull them down

#endif