#include "scene_configuration.h"

#include "placeholder/platformer_t_d.c"
#include "placeholder/background_m_b.c"

BOOLEAN has_scene_been_initialized = FALSE;

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

void scene_core_loop()
{
    scene_initialization(background_map, background_mapWidth, background_mapHeight);
}