#include "scene_configuration.h"
#include "sprites\LongSkateBgTiles.h"
#include "sprites\LongSkateBackground.h"
#include "sprites\MiscAssets.h"

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

UINT8 completed_loops = 0;

UINT16 background_mapWidth = 20;
UINT16 background_mapHeight = 200;

BOOLEAN intro_initialized = FALSE;

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

void intro_initialization()
{
    intro_initialized = TRUE;

    // we fill in 0-27 with player sprite data
    set_sprite_data(28, 4, MiscAssets);

    // we init player first and set 0 to 5 for player
    set_sprite_tile(6, 28);
    set_sprite_tile(7, 29);
    set_sprite_tile(8, 30);
    set_sprite_tile(9, 31);

    UINT8 x = 84;
    UINT8 y = 84;
    move_sprite(6, x, y);
    move_sprite(7, x + 8, y);
    move_sprite(8, x, y + 8);
    move_sprite(9, x + 8, y + 8);
}

void scene_initialization(const char *_background, UINT16 _map_width)
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

void scrollable_screen(const char *_background, UINT16 _map_width, UINT16 _map_height)
{
    // if((joypad() & J_DOWN) && (scrollY < _map_height - 18)) { tileCounter++; }

    if(scrollY < _map_height - 18) { tileCounter++; }
    else { completed_loops += 1; counter = 0; scrollY = 0; }

    if(tileCounter == 8)
    {
        scrollY++;
        tileCounter = 0;

        counter = _map_width * scrollY;

        for(temporary_y_index = 1; temporary_y_index != 20; temporary_y_index++)
        {
            set_bkg_tiles(0, temporary_y_index - 1, 22, 1, (unsigned char*)(_background + counter));

            counter += _map_width;
        }
    }
}

void intro_screen()
{

}

void scene_core_loop(BOOLEAN scene_is_intro)
{
    if (!scene_is_intro)
    {
        if(!has_scene_been_initialized)
        {
            scene_initialization(LongSkateBackground, LongSkateBackgroundWidth);
        }

        scrollable_screen(LongSkateBackground, LongSkateBackgroundWidth, LongSkateBackgroundHeight);
    }
    else
    {
        if (!intro_initialized)
        {
            intro_initialization();
        }
    }
}