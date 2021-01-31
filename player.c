#include "player.h"

#include "audio_configuration.h"
#include "game_configuration.h"
#include "scene_configuration.h"

#include "sprites/Skater.h"

BOOLEAN has_player_been_intialized = FALSE;
BOOLEAN has_reached_maximum_jump_height = FALSE;

UINT8 jump_delay = 0;
UINT8 jump_height = 10;
UINT8 sprites_in_use = 0;
UINT8 x_offset = 0; 
UINT8 y_offset = 0;

BOOLEAN initialize_player(struct player *_player)
{
    if(!has_player_been_intialized)
    {
        has_player_been_intialized = TRUE;

        _player->current_speed_y = 0;
        _player->gravity = -2;
        _player->player_height = 24;
        _player->index_top_left_x = 0;
        _player->index_top_left_y = 0;
        _player->jumping = 0;
        _player->player_state = 's';
        _player->player_position[0] = 80; _player->player_position[1] = 45;
        _player->tile_index_top_left = 0;
        _player->player_width = 16;

        set_sprite_data(0, 27, (unsigned char *)Skater);

        for(sprites_in_use = 0; sprites_in_use < 8; sprites_in_use++)
        {
            set_sprite_tile(sprites_in_use, sprites_in_use);
            
            move_sprite(sprites_in_use, _player->player_position[0] + x_offset, _player->player_position[1] + y_offset);

            if(sprites_in_use < 5)
            {
                x_offset += 8;

                if(x_offset == 16) {  x_offset = 0; y_offset += 8; }
            }
            else
            {
                x_offset -= 4;

                if(x_offset == 0) 
                {
                    x_offset = 4;
                    y_offset += 8;
                }
            }
        }

        x_offset = 0; y_offset = 0;
    }

    return has_player_been_intialized;
}

INT8 would_hit_surface(struct player *_player, UINT8 _projected_y_position)
{
    if(_projected_y_position >= _player->floor_y_position) { return _player->floor_y_position; }

    return -1;
}

unsigned char change_state(struct player *_player, char _state)
{
    switch(_state)
    {
        case 's':
            for(sprites_in_use = 0; sprites_in_use < 8; sprites_in_use++)
            {
                set_sprite_tile(sprites_in_use, sprites_in_use);
                
                move_sprite(sprites_in_use, _player->player_position[0] + x_offset, _player->player_position[1] + y_offset);

                if(sprites_in_use < 5)
                {
                    x_offset += 8;

                    if(x_offset == 16) {  x_offset = 0; y_offset += 8; }
                }
                else
                {
                    x_offset -= 4;

                    if(x_offset == 0) 
                    {
                        x_offset = 4;
                        y_offset += 8;
                    }
                }
            }
        break;
    }

    x_offset = 0; y_offset = 0;

    return _player->player_state;
}

void player_jump(struct player *_player, UINT8 _sprite_id)
{
    if(_player->jumping == 0 && scene_collision(0, _player->tile_index_top_left, _player->index_top_left_x, _player->index_top_left_y))
    {
        // For Matt in case he reads this, I forgot that a negative minus a negative equals a positive for a quick second. Oops ( =
        jump_height += _player->gravity;

        play_fx(0);

        _player->jumping = 1;
    }

    if(_player->jumping == 1)
    {
        if(!has_reached_maximum_jump_height) 
        {
            if(jump_height != 0)
            { 
                jump_delay += 1;

                if(jump_delay >= 3)
                {
                    jump_delay = 0;

                    jump_height -= 1;

                    _player->player_position[1] -= jump_height;

                    move_sprite(_sprite_id, _player->player_position[0], _player->player_position[1]);
                }
            }
            else 
            { 
                has_reached_maximum_jump_height = TRUE; 

                jump_delay = 0;
            }
        }
        else 
        {
            // Did it again, negative minus a negative equals a positive
            if(!scene_collision(0, _player->tile_index_top_left, _player->index_top_left_x, _player->index_top_left_y))
            {
                jump_delay += 1;

                if(jump_delay >= 3)
                {
                    jump_delay = 0;

                    jump_height += 1;

                    _player->player_position[1] += jump_height;

                    _player->index_top_left_x = (_player->player_position[0] - 8) / 8;
                    _player->index_top_left_y = (_player->player_position[1] - 16) / 8;
                    _player->tile_index_top_left = 32 * _player->index_top_left_y + _player->index_top_left_x;
                }

                if(scene_collision(0, _player->tile_index_top_left, _player->index_top_left_x, _player->index_top_left_y))
                {
                    UINT8 position_y_offset = _player->player_position[1] % 8;

                    if(position_y_offset != 0) { _player->player_position[1] -= position_y_offset; }
                }
            }
            else
            {
                has_reached_maximum_jump_height = FALSE;

                jump_height = 10;

                _player->jumping = 0;
            }

            move_sprite(_sprite_id, _player->player_position[0], _player->player_position[1]);
        }
    }
}

void player_movement(struct player *_player)
{
    if((joypad() & J_A) || _player->jumping == 1) { player_jump(_player, 0); }

    if (joypad() & J_LEFT && _player->index_top_left_x > 0 /* && !scene_collision(1, _player->tile_index_top_left, _player->index_top_left_x, _player->index_top_left_y) */)
    {
        _player->player_position[0] -= 2;

        for(sprites_in_use = 0; sprites_in_use < 8; sprites_in_use++)
        {            
            move_sprite(sprites_in_use, _player->player_position[0] + x_offset, _player->player_position[1] + y_offset);

            if(sprites_in_use < 5)
            {
                x_offset += 8;

                if(x_offset == 16) {  x_offset = 0; y_offset += 8; }
            }
            else
            {
                x_offset -= 4;

                if(x_offset == 0) 
                {
                    x_offset = 4;
                    y_offset += 8;
                }
            }
        }

        x_offset = 0; y_offset = 0;
    }

    if (joypad() & J_RIGHT && _player->index_top_left_x < 18 /* && !scene_collision(2, _player->tile_index_top_left, _player->index_top_left_x, _player->index_top_left_y) */)
    {
        _player->player_position[0] += 2;

        for(sprites_in_use = 0; sprites_in_use < 8; sprites_in_use++)
        {            
            move_sprite(sprites_in_use, _player->player_position[0] + x_offset, _player->player_position[1] + y_offset);

            if(sprites_in_use < 5)
            {
                x_offset += 8;

                if(x_offset == 16) {  x_offset = 0; y_offset += 8; }
            }
            else
            {
                x_offset -= 4;

                if(x_offset == 0) 
                {
                    x_offset = 4;
                    y_offset += 8;
                }
            }
        }

        x_offset = 0; y_offset = 0;
    }
}

void update_Player(struct player *_player)
{
    _player->index_top_left_x = (_player->player_position[0] - 8) / 8;
    _player->index_top_left_y = (_player->player_position[1] - 16) / 8;
    _player->tile_index_top_left = 32 * _player->index_top_left_y + _player->index_top_left_x;
}

void player_core_loop(struct player *_player)
{
    initialize_player(_player);

    player_movement(_player);
    
    update_Player(_player);
}