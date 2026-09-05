#include "player.h"
#include "bn_sprite_items_character.h"
#include "bn_sprite_items_hitbox_h.h"
#include "bn_sprite_items_hitbox_v.h"
#include "bn_keypad.h"


// Constructor
Player::Player(int start_x, int start_y) : 
    _sprite(bn::sprite_items::character.create_sprite(start_x, start_y)),
    // Initialize with Down-Walk frames (0, 1, 2, 3) running forever with a 10-frame delay
    _anim_action(bn::create_sprite_animate_action_forever(
        _sprite, 10, bn::sprite_items::character.tiles_item(), 0, 1, 2, 3)) 
{
}


void Player::update() 
{
    handle_invincibility();

    // Check if knocked back
    if(_state == PlayerState::KNOCKED_BACK)
    {
        handle_knockback();
    }
    // If not knocked back, check if attacking
    else if(_state == PlayerState::ATTACKING)
    {
        // Lock movement and process the attack animation/hitbox
        handle_attack();
    }
    // Normal movement and input handling
    else
    {
        // Allow movement
        handle_movement();
        
        // Listen for the attack input (mapped to A button)
        if(bn::keypad::a_pressed()) 
        {
            _state = PlayerState::ATTACKING;
            _attack_timer = 15; 
            
            // Create a visual debug sprite for the sword hitbox
            bn::fixed_rect hitbox = get_sword_hitbox();
            
            // Spawn the horizontal or vertical sprite based on facing direction
            if(_facing_direction == PlayerDirection::LEFT || _facing_direction == PlayerDirection::RIGHT)
            {
                _debug_hitbox_sprite = bn::sprite_items::hitbox_h.create_sprite(hitbox.x(), hitbox.y());
            }
            else
            {
                _debug_hitbox_sprite = bn::sprite_items::hitbox_v.create_sprite(hitbox.x(), hitbox.y());
            }
            
            _debug_hitbox_sprite->set_blending_enabled(true); 
        }
    }

    update_animations();
}


void Player::take_damage(int amount) 
{
    if(_invincibility_frames == 0) 
    {
        _hp -= amount;
        _invincibility_frames = 120;
    }
}


int Player::get_hp() const 
{
    return _hp; 
}


bn::fixed_rect Player::get_collision_rect() const 
{
    return bn::fixed_rect(_sprite.x(), _sprite.y(), 16, 16);
}


void Player::handle_movement() 
{
    int dx = 0;
    int dy = 0;

    if(bn::keypad::left_held())  { dx -= 1; }
    if(bn::keypad::right_held()) { dx += 1; }
    if(bn::keypad::up_held())    { dy -= 1; }
    if(bn::keypad::down_held())  { dy += 1; }

    if(dx == 0 && dy == 0)
    {
        _state = PlayerState::IDLE;
    }
    else
    {
        _state = PlayerState::MOVING;
        
        // Prioritize Left/Right facing over Up/Down for diagonal inputs
        if(dx < 0) {
            _facing_direction = PlayerDirection::LEFT;
        } else if(dx > 0) {
            _facing_direction = PlayerDirection::RIGHT;
        } else if(dy < 0) {
            _facing_direction = PlayerDirection::UP;
        } else if(dy > 0) {
            _facing_direction = PlayerDirection::DOWN;
        }
    }

    _sprite.set_x(_sprite.x() + dx);
    _sprite.set_y(_sprite.y() + dy);
}


bn::fixed_rect Player::get_sword_hitbox() const
{
    bn::fixed player_x = _sprite.x();
    bn::fixed player_y = _sprite.y();

    // Adjusted to match native 32x16 and 16x32 GBA sprite sizes
    switch(_facing_direction)
    {
        case PlayerDirection::LEFT:
            return bn::fixed_rect(player_x - 16, player_y, 32, 16);
        case PlayerDirection::RIGHT:
            return bn::fixed_rect(player_x + 16, player_y, 32, 16);
        case PlayerDirection::UP:
            return bn::fixed_rect(player_x, player_y - 16, 16, 32);
        case PlayerDirection::DOWN:
            return bn::fixed_rect(player_x, player_y + 16, 16, 32);
        default:
            return bn::fixed_rect(player_x, player_y, 16, 16);
    }
}


void Player::handle_attack()
{
    if(_attack_timer > 0)
    {
        _attack_timer--;
        
        // Update the visual debug sprite's position just in case the player moves slightly (if you allow movement later)
        if(_debug_hitbox_sprite)
        {
            bn::fixed_rect hitbox = get_sword_hitbox();
            _debug_hitbox_sprite->set_position(hitbox.x(), hitbox.y());
        }
    }
    else
    {
        _state = PlayerState::IDLE;
        
        // Destroy the visual debug sprite by resetting the optional wrapper
        _debug_hitbox_sprite.reset(); 
    }
}


void Player::handle_invincibility()
{
    if(_invincibility_frames > 0) 
    {
        _invincibility_frames--;
        _sprite.set_visible(_invincibility_frames % 4 != 0); 
    } 
    else 
    {
        _sprite.set_visible(true); 
    }
}


void Player::apply_knockback(bn::fixed dx, bn::fixed dy)
{
    // return early if already in knockback state
    if(_state == PlayerState::KNOCKED_BACK)
        return;
        
    _state = PlayerState::KNOCKED_BACK;
    _knockback_timer = 15; // 15 frames of locked movement
    _knockback_dx = dx;
    _knockback_dy = dy;
    
    // Safety check: if player was attacking when hit, immediately destroy the hitbox
    if(_debug_hitbox_sprite)
    {
        _debug_hitbox_sprite.reset();
    }

}


void Player::handle_knockback()
{
    if(_knockback_timer > 0)
    {
        _knockback_timer--;
        
        // Push the player in the knockback direction
        _sprite.set_x(_sprite.x() + _knockback_dx);
        _sprite.set_y(_sprite.y() + _knockback_dy);
    }
    else
    {
        // Knockback finished, return control
        _state = PlayerState::IDLE;
    }
}


void Player::update_animations()
{
    // Only update if the state or direction has changed
    if(_state != _previous_state || _facing_direction != _previous_direction)
    {
        if(_state == PlayerState::MOVING)
        {
            switch(_facing_direction)
            {
                case PlayerDirection::DOWN:  _anim_action = bn::create_sprite_animate_action_forever(_sprite, 10, bn::sprite_items::character.tiles_item(), 0, 1, 2, 3); break;
                case PlayerDirection::UP:    _anim_action = bn::create_sprite_animate_action_forever(_sprite, 10, bn::sprite_items::character.tiles_item(), 4, 5, 6, 7); break;
                case PlayerDirection::LEFT:  _anim_action = bn::create_sprite_animate_action_forever(_sprite, 10, bn::sprite_items::character.tiles_item(), 8, 9, 10, 11); break;
                case PlayerDirection::RIGHT: _anim_action = bn::create_sprite_animate_action_forever(_sprite, 10, bn::sprite_items::character.tiles_item(), 12, 13, 14, 15); break;
            }
        }
        else if(_state == PlayerState::ATTACKING)
        {
            // Attack frames (e.g., indices 16 through 31)
            // Use _once instead of _forever so the attack animation doesn't loop
            switch(_facing_direction)
            {
                case PlayerDirection::DOWN:  _anim_action = bn::create_sprite_animate_action_once(_sprite, 4, bn::sprite_items::character.tiles_item(), 16, 17, 18, 19); break;
                // ... (Add UP, LEFT, RIGHT attack cases) ...
            }
        }
        
        _previous_state = _state;
        _previous_direction = _facing_direction;
    }

    // Advance the animation by one frame
    _anim_action.update(); 
}