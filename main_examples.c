// #include <gb.h>
// #include <gb\font.h>
// #include <stdio.h>
// #include "sprites/SmilerSprites.c"

// #include "sprites/SimpleBackground.c"
// #include "sprites/SimpleBackgroundTiles.c"

// #include "sprites/WindowMap.c"


// // SOME SOUND PROGRAMMING A BASIC JUMP SOUND
// void main()
// {
//     // These registers must be in this specific order!!
//     NR52_REG = 0x80; // is 1000 0000 in binary and turns on sound
//     NR50_REG = 0x77; // sets the volume for both left and right channel just set to max 0x77
//     NR51_REG = 0xFF; // is 1111 1111 in binary, select which channels we want to use in this case all of them. 4 channels each with a bit for Left and Right

//     while(1)
//     {
//         UBYTE joypad_state = joypad();

//         if (joypad_state)
//         {
//             /* 
//                 see https://github.com/bwhitman/pushpin/blob/master/src/gbsound.txt
//                 channel 1 register 0: Frequency sweep settings
//                 7   Unused
//                 6-4 Sweep time (update rate) if 0, sweeping is off
//                 3   Sweet Direction (1: decrease, 0: increase)
//                 2-0 Sweep Right Shift (RtShift) amount (if 0, sweeping is off)

//                 7654 3210
//                 0001 0110 is 0x16, sweep time 1, sweep direction increase, shift amount per step 110 (6 decimal)
//             */
//             NR10_REG = 0x16;

//             /*
//                 channel 1 register 1: Wave pattern duty and sound length
//                 channels 1, 2, and 4
//                 7-6 wave pattern duty cycle 0-3 (12.5%, 25%, 50%, 75%), duty cycle is how long a quadrangular wave is "on" vs "off".
//                 5-0 sound length (higher the number shorter the sound)

//                 0100 0000 is 0x40, duty cycle 1 (25%), wave length 0 (long)
//             */
//            NR11_REG = 0x40;

//             /*
//                 channel 1 register 2: volume envelope (makes the colume get louder or quieter each "tick")
//                 on channels 1, 2, and 4
//                 7-4 (Initial) Channel Volume
//                 3   Volume sweep direction (0: down, 1: up)
//                 2-0 Length of each step in sweep (if 0, sweeping is off)

//                 NOTE: each step is n/64 seconds long, where n is 1-7
//                 // 0111 0011 is 0x73, volume 7, sweep down, step length 3
//             */
//            NR12_REG = 0x73;

//             /*
//                 channel 1 register 3: Frequency LSbs (Least Significant bits) and noise options
//                 for channels 1, 2, and 3
//                 7-0 8 least significant bits of frequency (3 most significant bits are set in register 4)
//             */
//             NR13_REG = 0x00;

//             /*
//                 channel 1 register 4: playback and frequency MSbs (Most Significant bits)
//                 channels 1, 2, 3, and 4
//                 7   Initialize (trigger channel start, AKA channel INIT) (Write only)
//                 6   Consecutive select/length counter enable (Read/Write).
//                         When "0", regardless of the length of data on the NR11 register, sound can be produced consecutively.
//                         When "1", sound is generated during the time period set by the length data contained in register NR11. 
//                         After the sound is ouput, the Sound 1 ON flag, at bit 0 of register NR52 is reset.
//                 5-3 Unused
//                 2-0 Most Significant bits of frequency
            
//                 1100 0011 is 0xC3, initialize, no consecutive, frequency = MSG + LSB = 011 0000 0000 = 0x300
//             */
//             NR14_REG = 0xC3;

//             delay(1000);
//         }
//     }
// }

// // Scrolling Background layer and HUD layer
// void main_2()
// {
//     // initialize font library
//     font_t min_font;
//     font_init();

//     // load font and set the font for use
//     min_font = font_load(font_min); // 36 tiles
//     font_set(min_font);

//     // load background data (start loading tiles after the font data since background and HUD layers share memory)
//     set_bkg_data(37, 7, backgroundtiles);
//     // set the background tiles
//     set_bkg_tiles(0, 0, 40, 18, backgroundmap);

//     // settings tiles for the HUD / window layer
//     set_win_tiles(0, 0, 5, 1, windowmap);
//     move_win(7, 120);

//     // show background layer
//     SHOW_BKG;
//     // show window layer
//     SHOW_WIN;
//     DISPLAY_ON;

//     while(1)
//     {
//         scroll_bkg(1, 0);

//         delay(100);
//     }
// }

// // THIS IS DRAWING A SPRITE AND MOVING IT
// void main_1()
// {
//     UINT8 currentSpriteIndex = 0;

//     // load tile data from 0 (first spot of array), and load 2 tiles total
//     set_sprite_data(0, 2, Smiler);

//     // set the first sprite to the first sprite from our tile data
//     set_sprite_tile(0, currentSpriteIndex);

//     // set initial position of sprite
//     move_sprite(0, 88, 78);

//     SHOW_SPRITES;

//     // gameloop
//     while(1)
//     {
//         switch (joypad())
//         {
//             case J_LEFT:
//                 scroll_sprite(0, -4, 0);
//                 break;
            
//             case J_RIGHT:
//                 scroll_sprite(0, 4, 0);
//                 break;
            
//             case J_UP:
//                 scroll_sprite(0, 0, -4);
//                 break;
            
//             case J_DOWN:
//                 scroll_sprite(0, 0, 4);
//                 break;
//         }

//         delay(100);
//     }
// }
