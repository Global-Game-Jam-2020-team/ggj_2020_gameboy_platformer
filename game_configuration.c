#include "game_configuration.h"

#include "audio_configuration.h"
#include "music_configuration.h"

UINT8 sprite_tile_number = 0;

void initialize_game()
{
    DISPLAY_OFF;

	HIDE_SPRITES;
	HIDE_WIN;
	HIDE_BKG;

    init_sfx();
    init_music();

    SWITCH_ROM_MBC1(2);

    SHOW_BKG;
    SHOW_SPRITES;

    DISPLAY_ON;
}

void performatdelay(UINT8 numloops)
{
    UINT8 i;

    for (i = 0; i < numloops; i++) { wait_vbl_done(); }
}