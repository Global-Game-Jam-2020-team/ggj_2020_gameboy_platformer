#include "game_configuration.h"

#include "audio_configuration.h"

UINT8 sprite_tile_number = 0;

void initialize_game()
{
    DISPLAY_ON;

    init_sfx();

    SHOW_BKG;
    SHOW_SPRITES;
}

void performatdelay(UINT8 numloops)
{
    UINT8 i;

    for (i = 0; i < numloops; i++) { wait_vbl_done(); }
}