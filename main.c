// Just to cleanup the GitHub repository, make sure to delete the files that are built by gbdk. ( =
#include <gb/gb.h>
#include <stdio.h>

#include "gbt_player.h"

#include "audio_configuration.h"
#include "game_configuration.h"
#include "player.h"
#include "scene_configuration.h"

struct player p;

extern const unsigned char * song_Data[];

int main()
{
    initialize_game();

     /*
        music stuff
    */    
    disable_interrupts();

    gbt_play(song_Data, 2, 7);
    gbt_loop(1);

    set_interrupts(VBL_IFLAG);
    enable_interrupts();

    while(TRUE)
    {
        player_core_loop(&p);
        scene_core_loop();

        performatdelay(1);
        gbt_update();
    }

    return 0;
}