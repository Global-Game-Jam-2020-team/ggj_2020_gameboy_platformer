#include "music_configuration.h"

// will be built by the music compiler tools during build process.
extern const unsigned char * song_gameplay_Data[];
extern const unsigned char * song_intro_Data[];

void init_music(const char name)
{  
    disable_interrupts();

    gbt_stop();

    if (name == 'g')
    {
        gbt_play(song_gameplay_Data, 3, 5);
    }

    if (name == 'i')
    {
        gbt_play(song_intro_Data, 3, 6);
    }

    gbt_loop(1);

    set_interrupts(VBL_IFLAG);
    enable_interrupts();
}
