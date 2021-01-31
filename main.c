// Just to cleanup the GitHub repository, make sure to delete the files that are built by gbdk. ( =
#include <gb/gb.h>
#include <stdio.h>

// #include "audio_configuration.h"
#include "game_configuration.h"
#include "player.h"
#include "scene_configuration.h"
#include "music/gbt_player.h"

struct player p;
BOOLEAN scene_is_intro = TRUE;

int main()
{
    initialize_game();

    while(TRUE)
    {
        scene_is_intro = player_core_loop(&p, scene_is_intro);
        scene_core_loop(scene_is_intro);

        performatdelay(1);
        gbt_update();
    }

    return 0;
}
