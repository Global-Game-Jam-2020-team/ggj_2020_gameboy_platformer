#include "player.h"

#include "audio_configuration.h"
#include "game_configuration.h"

BOOLEAN has_player_been_intialized = FALSE;

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
        _player->floor_y_position = 100;
        _player->gravity = -2;
        _player->jumping = 0;
        _player->player_position[0] = 10; _player->player_position[1] = _player->floor_y_position;

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
    INT8 possible_surface_y;

    if(_player->jumping == 0)
    {
        play_fx(0);

        _player->jumping = 1;

        _player->current_speed_y = 10;
    }

    _player->current_speed_y = _player->current_speed_y + _player->gravity;

    _player->player_position[1] -= _player->current_speed_y;

    possible_surface_y = would_hit_surface(_player, _player->player_position[1]);

    if(possible_surface_y > -1)
    {
        _player->jumping = 0;

        move_sprite(_sprite_id, _player->player_position[0], possible_surface_y);
    }
    else { move_sprite(_sprite_id, _player->player_position[0], _player->player_position[1]); }
}

void player_core_loop(struct player *_player)
{
    initialize_player(_player);

    if((joypad() & J_A) || _player->jumping == 1) { player_jump(_player, 0); }

    if (joypad() & J_LEFT)
    {
        _player->player_position[0] = _player->player_position[0] - 2;

        move_sprite(0, _player->player_position[0], _player->player_position[1]);
    }

    if (joypad() & J_RIGHT)
    {
        _player->player_position[0] = _player->player_position[0] + 2;

        move_sprite(0, _player->player_position[0], _player->player_position[1]);
    }
}