#include <gb/gb.h>
#include <stdio.h>

unsigned char bloke[] =
{
  0x00,0x00,0x38,0x38,0x7C,0x44,0x7F,0x7F,
  0x44,0x74,0x46,0x7C,0x40,0x78,0x24,0x3C,
  0x18,0x3C,0x00,0x24,0x00,0x24,0x00,0x24,
  0x00,0x24,0x00,0x36,0x00,0x00,0x00,0x00,
  0x00,0x00,0x38,0x38,0x7C,0x44,0x7F,0x7F,
  0x44,0x74,0x46,0x7C,0x40,0x78,0x24,0x3C,
  0x18,0x3C,0x00,0x22,0x00,0x22,0x00,0x22,
  0x00,0x23,0x00,0x30,0x00,0x00,0x00,0x00,
  0x00,0x00,0x38,0x38,0x7C,0x44,0x7F,0x7F,
  0x44,0x74,0x46,0x7C,0x40,0x78,0x24,0x3C,
  0x18,0x3C,0x00,0x42,0x00,0x42,0x00,0x42,
  0x00,0x42,0x00,0x63,0x00,0x00,0x00,0x00,
  0x00,0x00,0x38,0x38,0x7C,0x44,0x7F,0x7F,
  0x44,0x74,0x46,0x7C,0x40,0x78,0x24,0x3C,
  0x18,0x3C,0x00,0x44,0x00,0x44,0x00,0x44,
  0x00,0x64,0x00,0x06,0x00,0x00,0x00,0x00
};

INT8 playerlocation[2]; // stores two INT8 x and y positions of player
BYTE jumping;
INT8 gravity = -2;
UINT8 currentspeedY;
UINT8 floorYPosition = 100;

void init_sfx()
{
    // These registers must be in this specific order!!
    NR52_REG = 0x80; // is 1000 0000 in binary and turns on sound
    NR50_REG = 0x77; // sets the volume for both left and right channel just set to max 0x77
    NR51_REG = 0xFF; // is 1111 1111 in binary, select which channels we want to use in this case all of them. 4 channels each with a bit for Left and Right
}

void play_jump_fx()
{
    /* 
        see https://github.com/bwhitman/pushpin/blob/master/src/gbsound.txt
        channel 1 register 0: Frequency sweep settings
        7   Unused
        6-4 Sweep time (update rate) if 0, sweeping is off
        3   Sweet Direction (1: decrease, 0: increase)
        2-0 Sweep Right Shift (RtShift) amount (if 0, sweeping is off)

        7654 3210
        0001 0110 is 0x16, sweep time 1, sweep direction increase, shift amount per step 110 (6 decimal)
    */
    NR10_REG = 0x16;

    /*
        channel 1 register 1: Wave pattern duty and sound length
        channels 1, 2, and 4
        7-6 wave pattern duty cycle 0-3 (12.5%, 25%, 50%, 75%), duty cycle is how long a quadrangular wave is "on" vs "off".
        5-0 sound length (higher the number shorter the sound)

        0100 0000 is 0x40, duty cycle 1 (25%), wave length 0 (long)
    */
    NR11_REG = 0x40;

    /*
        channel 1 register 2: volume envelope (makes the colume get louder or quieter each "tick")
        on channels 1, 2, and 4
        7-4 (Initial) Channel Volume
        3   Volume sweep direction (0: down, 1: up)
        2-0 Length of each step in sweep (if 0, sweeping is off)

        NOTE: each step is n/64 seconds long, where n is 1-7
        // 0111 0011 is 0x73, volume 7, sweep down, step length 3
    */
    NR12_REG = 0x73;

    /*
        channel 1 register 3: Frequency LSbs (Least Significant bits) and noise options
        for channels 1, 2, and 3
        7-0 8 least significant bits of frequency (3 most significant bits are set in register 4)
    */
    NR13_REG = 0x00;

    /*
        channel 1 register 4: playback and frequency MSbs (Most Significant bits)
        channels 1, 2, 3, and 4
        7   Initialize (trigger channel start, AKA channel INIT) (Write only)
        6   Consecutive select/length counter enable (Read/Write).
                When "0", regardless of the length of data on the NR11 register, sound can be produced consecutively.
                When "1", sound is generated during the time period set by the length data contained in register NR11. 
                After the sound is ouput, the Sound 1 ON flag, at bit 0 of register NR52 is reset.
        5-3 Unused
        2-0 Most Significant bits of frequency
    
        1100 0011 is 0xC3, initialize, no consecutive, frequency = MSG + LSB = 011 0000 0000 = 0x300
    */
    NR14_REG = 0xC3;
}

void performatdelay(UINT8 numloops)
{
    UINT8 i;

    for (i = 0; i < numloops; i++)
    {
        wait_vbl_done();
    }
}

INT8 wouldhitsurface(UINT8 projectedYPosition)
{
    if (projectedYPosition >= floorYPosition) {
        return floorYPosition;
    }

    return -1;
}

void jump(UINT8 spriteid, UINT8 spritelocation[2])
{
    INT8 possiblesurfaceY;

    if (jumping == 0)
    {
        play_jump_fx();
        jumping = 1;
        currentspeedY = 10;
    }

    currentspeedY = currentspeedY + gravity;

    spritelocation[1] = spritelocation[1] - currentspeedY;

    possiblesurfaceY = wouldhitsurface(spritelocation[1]);

    if (possiblesurfaceY > -1)
    {
        jumping = 0;
        move_sprite(spriteid, spritelocation[0], possiblesurfaceY);
    }
    else
    {
        move_sprite(spriteid, spritelocation[0], spritelocation[1]);
    }
}

void main()
{
    init_sfx();

    set_sprite_data(0, 8, bloke);
    set_sprite_tile(0, 0);

    playerlocation[0] = 10;
    playerlocation[1] = floorYPosition;

    move_sprite(0, playerlocation[0], playerlocation[1]);
    jumping = 0;

    DISPLAY_ON;
    SHOW_SPRITES;

    while(1)
    {
        if ((joypad() & J_A) || jumping == 1)
        {
            jump(0, playerlocation);
        }

        if (joypad() & J_LEFT)
        {
            playerlocation[0] = playerlocation[0] - 2;
            move_sprite(0, playerlocation[0], playerlocation[1]);
        }

        if (joypad() & J_RIGHT)
        {
            playerlocation[0] = playerlocation[0] + 2;
            move_sprite(0, playerlocation[0], playerlocation[1]);
        }

        performatdelay(5);
    }
}
