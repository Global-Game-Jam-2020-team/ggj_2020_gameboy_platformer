#include "player.h"

#include "audio_configuration.h"
#include "game_configuration.h"
#include "scene_configuration.h"

BOOLEAN has_player_been_intialized = FALSE;
BOOLEAN has_reached_maximum_jump_height = FALSE;

UINT8 jump_height = 10;

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

BOOLEAN initialize_player(struct player *_player)
{
    if(!has_player_been_intialized)
    {
        has_player_been_intialized = TRUE;

        _player->current_speed_y = 0;
        _player->floor_y_position = 112;
        _player->gravity = -2;
        _player->index_top_left_x = 0;
        _player->index_top_left_y = 0;
        _player->jumping = 0;
        _player->player_position[0] = 10; _player->player_position[1] = _player->floor_y_position;
        _player->tile_index_top_left = 0;

        set_sprite_data(0, 8, bloke);
        set_sprite_tile(0, 0);

        move_sprite(0, _player->player_position[0], _player->player_position[1]);
    }

    return has_player_been_intialized;
}

INT8 would_hit_surface(struct player *_player, UINT8 _projected_y_position)
{
    if(_projected_y_position >= _player->floor_y_position) { return _player->floor_y_position; }

    return -1;
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

    // Here's the plan, we are gonna have a variable which is called jump_height,
    // We will set it here, then once you press to jump, it will be affected by gravity
    // We will have a loop check to see how long it takes to gt to the top of the jump height
    // once it reaches the top, go back dowm
    // once it does, check jump to off but also check if it will hit the floor, if yes, also stop jumping

    if(_player->jumping == 1)
    {
        if(!has_reached_maximum_jump_height) 
        {
            if(jump_height != 0)
            { 
                // printf("%d\n", (UINT16)jump_height); delay(999);
                jump_height -= 1;

                _player->player_position[1] -= jump_height;

                move_sprite(_sprite_id, _player->player_position[0], _player->player_position[1]);
            }
            else { has_reached_maximum_jump_height = TRUE; }
        }
        else 
        {
            // Did it again, negative minus a negative equals a positive
            if(jump_height == 5 /*|| scene_collision(0, _player->tile_index_top_left, _player->index_top_left_x, _player->index_top_left_y)*/)
            {
                has_reached_maximum_jump_height = FALSE;

                jump_height = 10;

                _player->jumping = 0;
            }

            jump_height += 1;

            _player->player_position[1] += jump_height;

            move_sprite(_sprite_id, _player->player_position[0], _player->player_position[1]);
        }
    }

    // INT8 possible_surface_y;

    // if(_player->jumping == 0)
    // {
    //     play_fx(0);

    //     _player->jumping = 1;

    //     _player->current_speed_y = 10;
    // }

    // _player->current_speed_y = _player->current_speed_y + _player->gravity;

    // _player->player_position[1] -= _player->current_speed_y;

    // possible_surface_y = would_hit_surface(_player, _player->player_position[1]);

    // if(possible_surface_y > -1)
    // {
    //     _player->jumping = 0;

    //     move_sprite(_sprite_id, _player->player_position[0], possible_surface_y);
    // }
    // else { move_sprite(_sprite_id, _player->player_position[0], _player->player_position[1]); }
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

    if((joypad() & J_A) || _player->jumping == 1) { player_jump(_player, 0); }

    if (joypad() & J_LEFT && !scene_collision(1, _player->tile_index_top_left, _player->index_top_left_x, _player->index_top_left_y))
    {
        _player->player_position[0] = _player->player_position[0] - 2;

        move_sprite(0, _player->player_position[0], _player->player_position[1]);
    }

    if (joypad() & J_RIGHT && !scene_collision(2, _player->tile_index_top_left, _player->index_top_left_x, _player->index_top_left_y))
    {
        _player->player_position[0] = _player->player_position[0] + 2;

        move_sprite(0, _player->player_position[0], _player->player_position[1]);
    }

    update_Player(_player);
}