// Just to cleanup the GitHub repository, make sure to delete the files that are built by gbdk. ( =
#include <gb/gb.h>
#include <stdio.h>

#include "audio_configuration.h"
#include "game_configuration.h"
#include "player.h"
#include "scene_configuration.h"
#include "music/gbt_player.h"


// Matt testing grounds includes start 
    // #include "sprites/Skater.h"
    // #include "sprites/SpiritSkater.h"
    // #include "sprites/MiscAssets.h"
// Matt testing grounds includes end

/*
Misc Assets Sprite table (putting in main.c temporarily)
    MiscAssets.c
        Grave 0-3
            [00][01]
            [02][03]

        Mud Pit (for jumping) 4-11
            [04][05][06][07]
            [08][09][10][11]

        Barricade (for crouching) 12-19
            [12][13][14][15]
            [16][17][18][19]
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


// UINT8 i;
// UINT8 x1;
// UINT8 x2;
// UINT8 y1;
// UINT8 y2;
void matts_testing_grounds()
{
   

    // spirit skater sprites start
        // x1 = 50;
        // y1 = 50;
        // x2 = 70;
        // set_sprite_data(0, 16, SpiritSkater);

        // for (i = 0; i < 16; ++i)
        // {
        //     set_sprite_tile(i, i);
        // }

        // move_sprite(0, x1, y1);
        // move_sprite(1, x1 + 8, y1);
        // move_sprite(2, x1, y1 + 8);
        // move_sprite(3, x1 + 8, y1+ 8);
        // move_sprite(4, x1, y1+16);
        // move_sprite(5, x1 + 8, y1+16);
        // move_sprite(6, x1, y1+24);
        // move_sprite(7, x1 + 8, y1+24);

        // move_sprite(8, x2, y1);
        // move_sprite(9, x2 + 8, y1);
        // move_sprite(10, x2, y1 + 8);
        // move_sprite(11, x2 + 8, y1+ 8);
        // move_sprite(12, x2, y1+16);
        // move_sprite(13, x2 + 8, y1+16);
        // move_sprite(14, x2, y1+24);
        // move_sprite(15, x2 + 8, y1+24);
    // spirit skater sprites end

    // grave & player start
        // x1 = 62;
        // x2 = 80;
        // y1 = 50;
        // y2 = 43;
        // set_sprite_data(0, 4, MiscAssets);

        // for (i = 0; i < 4; ++i)
        // {
        //     set_sprite_tile(i,i);
        // }

        // move_sprite(0, x2, y1);
        // move_sprite(1, x2 + 8, y1);
        // move_sprite(2, x2, y1+8);
        // move_sprite(3, x2 + 8, y1+8);

        // set_sprite_data(4, 27, Skater);

        // for (i = 4; i < 27+4; ++i)
        // {
        //     set_sprite_tile(i, i);
        // }

        // move_sprite(25, x1, y2);
        // move_sprite(26, x1+8, y2);
        // move_sprite(27, x1, y2+8);
        // move_sprite(28, x1+8, y2+8);
        // move_sprite(29, x1, y2+16);
        // move_sprite(30, x1+8, y2+16);
    // gave & player end

    // obstacles start
        // x1 = 50;
        // y1 = 50;
        // y2 = 80;
        // set_sprite_data(0, 20, MiscAssets);

        // for (i = 0; i < 20; ++i)
        // {
        //     set_sprite_tile(i, i);
        // }

        // move_sprite(4, x1, y1);
        // move_sprite(5, x1 + 8, y1);
        // move_sprite(6, x1 + 16, y1);
        // move_sprite(7, x1 + 24, y1);
        // move_sprite(8, x1, y1 + 8);
        // move_sprite(9, x1 + 8, y1 + 8);
        // move_sprite(10, x1 + 16, y1 + 8);
        // move_sprite(11, x1 + 24, y1 + 8);

        // move_sprite(12, x1, y2);
        // move_sprite(13, x1 + 8, y2);
        // move_sprite(14, x1 + 16, y2);
        // move_sprite(15, x1 + 24, y2);
        // move_sprite(16, x1, y2 + 8);
        // move_sprite(17, x1 + 8, y2 + 8);
        // move_sprite(18, x1 + 16, y2 + 8);
        // move_sprite(19, x1 + 24, y2 + 8);
    // obstacles end
}

struct player p;

int main()
{
    initialize_game();

    // matts_testing_grounds();
    // return 0;

    while(TRUE)
    {
        player_core_loop(&p);
        scene_core_loop();

        performatdelay(1);
        gbt_update();
    }

    return 0;
}
