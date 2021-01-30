#include "scene_configuration.h"

#include "placeholder/platformer_t_d.c"
#include "placeholder/background_m_b.c"

BOOLEAN has_scene_been_changed = FALSE;
BOOLEAN has_scene_been_initialized = FALSE;

UINT8 count_A = 0, count_B = 0;

UINT16 tile_index_X = 0, tile_index_X_Decrement = 0;
UINT16 tile_Offset = 0;
UINT16 position_X = 0;

const char blank_tile[1] = {0x00};

// Down = 0 // Left = 1 // Right = 2 // Up = 3
BOOLEAN scene_collision(UINT8 _direction, UINT16 _player_index_top_left, UINT16 _player_index_top_left_x, UINT16 _player_index_top_left_y)
{
    switch(_direction)
    {
        // Down
        case 0: if(background_map[_player_index_top_left + background_mapWidth] != blank_tile[0] || _player_index_top_left_y == background_mapHeight) { return TRUE; } break;
        // Left
        case 1: if(background_map[_player_index_top_left] != blank_tile[0] || _player_index_top_left_x == 0) { return TRUE; } break;
        // Right
        case 2: if(background_map[_player_index_top_left + 1] != blank_tile[0] || _player_index_top_left_x == background_mapWidth) { return TRUE; } break;
        // Up
        case 3: if(background_map[_player_index_top_left - background_mapWidth] != blank_tile[0] || _player_index_top_left_y == 0) { return TRUE; } break;
    }
    // Default
    return FALSE;
}

BOOLEAN scene_initialization(const char *_map, UINT16 _map_width, UINT16 _map_height)
{
    if(!has_scene_been_initialized)
    {
        has_scene_been_initialized = TRUE;

        set_bkg_data(0, 11, platformer_sprites);
        set_bkg_tiles(0, 0, _map_width, _map_height, (unsigned char *)_map);
    }

    return 1;
}

void scene_transition(const char *_background, UINT8 _direction, UINT8 _width_background)
{
    // set_bkg_tiles(0, 0, 32, 18, (unsigned char *)_background);
    // delay(1500);
    // set_bkg_tiles(1, 0, 1, 1, (unsigned char *)_background[8]);

    UINT8 screen_panned_x = 0; UINT8 screen_panned_y = 0; 
    // You will only need to pan / translate the screen in any direction by 20
    UINT8 screen_tiles_panned = 0;

    for(; screen_tiles_panned < 20; screen_tiles_panned++)
    {
        UINT8 temporary_screen_tiles_panned = 1 + screen_tiles_panned;

        // Right - Pan everything to the left
        // First move the previous background to the left by one (8 pixels).
        // Where gonna have to set the last column on the right side (19) of the screen to the first column of the new background
        if(_direction == 2)
        {
            // scroll_bkg(8, 0);
            
            for(; temporary_screen_tiles_panned > screen_tiles_panned; temporary_screen_tiles_panned--)
            {
                UINT8 column_element_counter = 0;

                for(; column_element_counter < 18; column_element_counter++) 
                {
                    // printf("%d\n", (UINT16)column_element_counter); delay(250);
                    set_bkg_tiles(20 - temporary_screen_tiles_panned, column_element_counter, 1, 1, (unsigned char *)_background[(temporary_screen_tiles_panned - 1) + (_width_background * column_element_counter)]);
                    delay(250);
                }
            }
        }
    }
}

void scrollable_screen(const char *_background, UINT16 _map_width, UINT16 _map_height)
{
    // if((d_Pad & J_LEFT) && (tile_index_X != 0)){
    //     position_X--;
    //     tile_index_X_Decrement++;
    //     scroll_bkg(-1, 0);
    // }
    
    if((joypad() & J_RIGHT) && (tile_index_X < _map_width - 20)){
        position_X++;
        tile_index_X_Decrement--;
        scroll_bkg(1, 0);
    }

    if(position_X == 8){
        position_X = 0;

        tile_index_X++;
        tile_index_X_Decrement = 0;

        tile_Offset = tile_index_X + 21;

        count_B = tile_Offset % 32;

        for(count_A = 0; count_A != _map_height; count_A++){     
            set_bkg_tiles(count_B, count_A, 1, 1, (unsigned char *)(_background + tile_Offset));

            tile_Offset = tile_Offset + _map_width;
        }
    }
    
    // if(tile_index_X_Decrement == 8){
    //     position_X = 0;

    //     tile_index_X--;
    //     tile_index_X_Decrement = 0;

    //     tile_Offset = tile_index_X - 1;

    //     count_B = tile_Offset % 32;

    //     for(count_A = 0; count_A != 18; count_A++){     
    //         set_bkg_tiles(count_B, count_A, 1, 1, &(testMapTwo + tile_Offset));

    //         tile_Offset = tile_Offset + 256;
    //     }
    // }
}

void scene_core_loop()
{
    scene_initialization(background_map, background_mapWidth, background_mapHeight);
}