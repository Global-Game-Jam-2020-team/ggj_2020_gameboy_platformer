#include "music_configuration.h"

// will be built by the music compiler tools during build process.
extern const unsigned char * song_Data[];

void init_music()
{  
    disable_interrupts();

    gbt_play(song_Data, 2, 7);
    gbt_loop(1);

    set_interrupts(VBL_IFLAG);
    enable_interrupts();
}
