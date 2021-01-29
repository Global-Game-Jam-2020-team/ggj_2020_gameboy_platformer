#ifndef MUSIC_CONFIGURATION_H
#define MUSIC_CONFIGURATION_H

#include <gb/gb.h>
#include <stdio.h>

#include "gbt_player.h"

// will be built by the music compiler tools during build process.
extern const unsigned char * song_Data[];

void init_music();

#endif
