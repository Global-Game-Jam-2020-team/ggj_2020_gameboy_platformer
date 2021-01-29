// Just to cleanup the GitHub repository, make sure to delete the files that are built by gbdk. ( =
#include <gb/gb.h>
#include <stdio.h>

#include "audio_configuration.h"
#include "game_configuration.h"
#include "player.h"
#include "scene_configuration.h"
#include "gbt_player.h"

struct player p;

int main()
{
    initialize_game();

    while(TRUE)
    {
        player_core_loop(&p);
        scene_core_loop();

        performatdelay(1);
        gbt_update();
    }

    return 0;
}