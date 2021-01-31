#include "scene_configuration.h"
#include "sprites\LongSkateBgTiles.h"
#include "sprites\LongSkateBackground.h"

// Insert your tile and background #include below
// #include "placeholder/platformer_t_d.c"
// #include "placeholder/background_m_b.c"
// Insert your tile and background #include above

BOOLEAN has_scene_been_changed = FALSE;
BOOLEAN has_scene_been_initialized = FALSE;

BYTE tileCounter = 0;

UBYTE scrollY = 0;
UBYTE temporary_x_index = 0; UBYTE temporary_y_index = 0;

UWORD counter = 0;

const char blank_tile[1] = {0x00};

UINT16 background_mapWidth = 20;
UINT16 background_mapHeight = 200;

// Down = 0 // Left = 1 // Right = 2 // Up = 3
BOOLEAN scene_collision(UINT8 _direction, UINT16 _player_index_top_left, UINT16 _player_index_top_left_x, UINT16 _player_index_top_left_y)
{
    switch(_direction)
    {
        // Down
        case 0: if(LongSkateBackground[_player_index_top_left + background_mapWidth] != blank_tile[0] || _player_index_top_left_y == background_mapHeight) { return TRUE; } break;
        // Left
        case 1: if(LongSkateBackground[_player_index_top_left] != blank_tile[0] || _player_index_top_left_x == 0) { return TRUE; } break;
        // Right
        case 2: if(LongSkateBackground[_player_index_top_left + 1] != blank_tile[0] || _player_index_top_left_x == background_mapWidth) { return TRUE; } break;
        // Up
        case 3: if(LongSkateBackground[_player_index_top_left - background_mapWidth] != blank_tile[0] || _player_index_top_left_y == 0) { return TRUE; } break;
    }
    // Default
    return FALSE;
}

BOOLEAN scene_initialization(const char *_background, UINT16 _map_width)
{
    if(!has_scene_been_initialized)
    {
        has_scene_been_initialized = TRUE;

        // Insert your tile data below
        set_bkg_data(0, 26, LongSkateBgTiles);
        // Insert your tile data above

        counter = 0;
        for(temporary_y_index = 0; temporary_y_index != 18; temporary_y_index++)
        {
            set_bkg_tiles( 0, temporary_y_index, 22, 1, (unsigned char*)(_background + counter));
            counter = counter + _map_width;
        }
    }

    return 1;
}

void scrollable_screen(const char *_background, UINT16 _map_width, UINT16 _map_height)
{
    // if((joypad() & J_DOWN) && (scrollY < _map_height - 18)) { tileCounter++; }

    if(scrollY < _map_height - 18) { tileCounter++; }
    else { counter = 0; scrollY = 0; }

    if(tileCounter == 8)
    {
        scrollY++;
        tileCounter = 0;

        counter = _map_width * scrollY;

        for(temporary_y_index = 0; temporary_y_index != 20; temporary_y_index++)
        {
            if(temporary_y_index != 0)
            {
                for(temporary_x_index = 0; temporary_x_index != _map_width; temporary_x_index++)
                {
                    if(temporary_x_index < 20) { set_bkg_tiles(temporary_x_index, temporary_y_index - 1, 1, 1, (unsigned char*)(_background + counter)); }
                    counter += 1;
                }
            }
        }
    }
}

void scene_core_loop()
{
    // Insert your background information below
    scene_initialization(LongSkateBackground, background_mapWidth);

    scrollable_screen(LongSkateBackground, background_mapWidth, background_mapHeight);
    // Insert your background information above
}