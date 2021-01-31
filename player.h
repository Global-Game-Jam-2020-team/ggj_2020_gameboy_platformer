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

    UINT8 player_width;
    UINT8 player_height;

    UINT16 index_top_left_x;
    UINT16 index_top_left_y;
    UINT16 tile_index_top_left;

    // Will keep track of the player's current position on screen
    UINT16 player_position[2];

    // standing w/ skateboard - s
    // crouching - c
    // jumping w/ skateboard - j
    // backside looking at grave - b
    unsigned char player_state;
};

extern BOOLEAN has_player_been_intialized;

void init_intro_player();

BOOLEAN intro_wait_for_input();

void initialize_player(struct player *);

INT8 would_hit_surface(struct player *, UINT8);

unsigned char change_state(struct player *, char);

void player_jump(struct player *, UINT8);

void player_movement(struct player *);

void update_Player(struct player *);

// Anything that happens within the player, will occurr in this loop
BOOLEAN player_core_loop(struct player *, BOOLEAN scene_is_intro);

#endif