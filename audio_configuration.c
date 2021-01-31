// #include "audio_configuration.h"

// void init_sfx()
// {
//     // These registers must be in this specific order!!
//     NR52_REG = 0x80; // is 1000 0000 in binary and turns on sound
//     NR50_REG = 0x77; // sets the volume for both left and right channel just set to max 0x77
//     NR51_REG = 0xFF; // is 1111 1111 in binary, select which channels we want to use in this case all of them. 4 channels each with a bit for Left and Right
// }

// // Sfx labels
// // 0 - jump
// void play_fx(UINT8 _sfx_label)
// {
//     switch(_sfx_label)
//     {
//         case 0:
//             NR10_REG = 0x16;
//             NR11_REG = 0x40;
//             NR12_REG = 0x73;
//             NR13_REG = 0x00;
//             NR14_REG = 0xC3;
//         break;
//     }
// }