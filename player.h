#ifndef PLAYER_H
#define PLAYER_H

#include <gb/gb.h>

/*
Skater sprites table:
    Skater.c
        standing 1-6
            [01][02]
            [03][04]
            [05][06]

        skateboard 7-8
            [07]
            [08]

        crouching: 9-14
            [09][10]
            [11][12]
            [13][14]
        
        jumping 15-20
            [15][16]
            [17][18]
            [19][20]

        skateboard while jumping 21
            [21]

        backside looking at grave 22-27
            [22][23]
            [24][25]
            [26][27]

        small shadow for jumping or anything shadow related 28
            [28]
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

void player_jump(struct player *);

void player_movement(struct player *);

void update_Player(struct player *);

// Anything that happens within the player, will occurr in this loop
BOOLEAN player_core_loop(struct player *, BOOLEAN scene_is_intro);

#endif