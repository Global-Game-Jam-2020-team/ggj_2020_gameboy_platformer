#include "player.h"

#include "game_configuration.h"
#include "scene_configuration.h"

#include "sprites/Skater.h"

BOOLEAN has_player_been_intialized = FALSE;
BOOLEAN has_reached_maximum_jump_height = FALSE;
BOOLEAN will_switch_state = FALSE;

BOOLEAN intro_player_initialized = FALSE;

UINT8 jump_delay = 0;
UINT8 jump_height = 10;
UINT8 sprites_in_use = 0;
UINT8 sprites_to_use = 0;
UINT8 x_offset = 0; 
UINT8 y_offset = 0;

void init_intro_player()
{
    UINT8 i;
    intro_player_initialized = TRUE;
    set_sprite_data(0, 28, (unsigned char *)Skater);

    for (i = 22; i < 28; ++i)
    {
        set_sprite_tile(i - 22, i);
        sprites_in_use += 1;
    }

    printf("                                                                Skate or Cry");
    printf("                             Press Start");

    UINT8 x = 70;
    UINT8 y = 80;
    move_sprite(0, x, y);
    move_sprite(1, x + 8, y);
    move_sprite(2, x, y + 8);
    move_sprite(3, x + 8, y + 8);
    move_sprite(4, x, y + 16);
    move_sprite(5, x + 8, y + 16);
}

void initialize_player(struct player *_player)
{
    UINT8 temporary_counter = 0;
    for(; temporary_counter < 40; temporary_counter++) { set_sprite_tile(temporary_counter, 0); }
   
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

    set_sprite_data(0, 28, (unsigned char *)Skater);

    sprites_to_use = 1;

    for(sprites_in_use = 1; sprites_in_use < 9; sprites_in_use++)
    {
        set_sprite_tile(sprites_to_use, sprites_in_use);
        
        sprites_to_use += 1;
        
        move_sprite(sprites_in_use, _player->player_position[0] + x_offset, _player->player_position[1] + y_offset);

        if(sprites_in_use < 6)
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

INT8 would_hit_surface(struct player *_player, UINT8 _projected_y_position)
{
    if(_projected_y_position >= _player->floor_y_position) { return _player->floor_y_position; }

    return -1;
}

unsigned char change_state(struct player *_player, char _state)
{
    if(will_switch_state)
    {
        UINT8 sprite_reset = 0;

        will_switch_state = FALSE;

        for(; sprite_reset < sprites_to_use; sprite_reset++) { set_sprite_tile(sprite_reset, 0); }
        
        sprites_to_use = 1;

        switch(_state)
        {
            case 's':
                for(sprites_in_use = 1; sprites_in_use < 9; sprites_in_use++)
                {
                    set_sprite_tile(sprites_to_use, sprites_in_use);
                    
                    sprites_to_use += 1;
                    
                    move_sprite(sprites_in_use, _player->player_position[0] + x_offset, _player->player_position[1] + y_offset);

                    if(sprites_in_use < 6)
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
            case 'j':
                for(sprites_in_use = 15; sprites_in_use < 22; sprites_in_use++)
                {
                    set_sprite_tile(sprites_to_use, sprites_in_use);
                
                    sprites_to_use += 1;
                    
                    move_sprite(sprites_in_use, _player->player_position[0] + x_offset, _player->player_position[1] + y_offset);

                    if(sprites_in_use < 20)
                    {
                        x_offset += 8;

                        if(x_offset == 16) {  x_offset = 0; y_offset += 8; }
                    }
                    else
                    {
                        x_offset -= 3;
                        y_offset += 3;
                    }
                }
            break;
        }

        x_offset = 0; y_offset = 0;
    }

    return _player->player_state;
}

void player_jump(struct player *_player)
{
    if(_player->jumping == 0)
    {
        // play_fx(0);

        _player->jumping = 1;
        _player->player_state = 'j';
        will_switch_state = TRUE;

        change_state(_player, _player->player_state);
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
            if(jump_height != 10)
            {
                jump_delay += 1;

                if(jump_delay >= 3)
                {
                    jump_delay = 0;

                    jump_height += 1;
                }
            }
            else
            {
                has_reached_maximum_jump_height = FALSE;

                jump_height = 10;

                _player->jumping = 0;

                _player->player_state = 's';
                will_switch_state = TRUE;

                change_state(_player, _player->player_state);
            }
        }
    }
}

BOOLEAN intro_wait_for_input()
{
    if (joypad() & J_START)
    {
       return FALSE;
    }

    return TRUE;
}

void player_movement(struct player *_player)
{
    if((joypad() & J_A) || _player->jumping == 1) { player_jump(_player); }

    if(_player->jumping != 1)
    {
        if (joypad() & J_LEFT && _player->index_top_left_x > 0 /* && !scene_collision(1, _player->tile_index_top_left, _player->index_top_left_x, _player->index_top_left_y) */)
        {
            _player->player_position[0] -= 2;

            for(sprites_in_use = 1; sprites_in_use < 9; sprites_in_use++)
            {            
                move_sprite(sprites_in_use, _player->player_position[0] + x_offset, _player->player_position[1] + y_offset);

                if(sprites_in_use < 6)
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

            for(sprites_in_use = 1; sprites_in_use < 9; sprites_in_use++)
            {            
                move_sprite(sprites_in_use, _player->player_position[0] + x_offset, _player->player_position[1] + y_offset);

                if(sprites_in_use < 6)
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
}

void update_Player(struct player *_player)
{
    _player->index_top_left_x = (_player->player_position[0] - 8) / 8;
    _player->index_top_left_y = (_player->player_position[1] - 16) / 8;
    _player->tile_index_top_left = 32 * _player->index_top_left_y + _player->index_top_left_x;
}

BOOLEAN player_core_loop(struct player *_player, BOOLEAN scene_is_intro)
{
    if (!scene_is_intro)
    {
        if(!has_player_been_intialized)
        {
            initialize_player(_player);
        }

        // we are in gameplay
        if (completed_loops < max_completed_loops)
        {
            player_movement(_player);
            
            update_Player(_player);
        }

        // we are in outro
        if (completed_loops >= max_completed_loops)
        {
            // make sure player is in standing state for outro
            // if (_player->player_state != 's')
            // {
            //     change_state(_player, 's');
            // }

            // keey player in same position during outro
            if (_player->player_position[0] != 40 || _player->player_position[1] != 45)
            {
                _player->player_position[0] = 60;
                _player->player_position[1] = 45;

                for(sprites_in_use = 1; sprites_in_use < 9; sprites_in_use++)
                {            
                    move_sprite(sprites_in_use, _player->player_position[0] + x_offset, _player->player_position[1] + y_offset);

                    if(sprites_in_use < 6)
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
    }
    else
    {
        if (!intro_player_initialized)
        {
            init_intro_player();
        }

        scene_is_intro = intro_wait_for_input();
    }

    return scene_is_intro;
}