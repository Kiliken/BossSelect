#include "player.h"
#include "bn_sprite_items_character.h"
#include "bn_keypad.h"


// Constructor
Player::Player(int start_x, int start_y) : 
    _sprite(bn::sprite_items::character.create_sprite(start_x, start_y)) 
{
}


void Player::update() 
{
    handle_invincibility();

    if(_state == PlayerState::ATTACKING)
    {
        // Lock movement and process the attack animation/hitbox
        handle_attack();
    }
    else
    {
        // Allow movement
        handle_movement();
        
        // Listen for the attack input (mapped to A button)
        if(bn::keypad::a_pressed()) 
        {
            _state = PlayerState::ATTACKING;
            _attack_timer = 15; // Set attack duration to 15 frames (1/4th of a second)
            
            // TODO: Spawn the sword sprite in the _facing_direction
        }
    }
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

    // State & Direction updating
    if(dx == 0 && dy == 0)
    {
        _state = PlayerState::IDLE;
    }
    else
    {
        _state = PlayerState::MOVING;
        
        // Update facing direction based on input combinations
        if(dx < 0 && dy < 0)      _facing_direction = PlayerDirection::UP_LEFT;
        else if(dx > 0 && dy < 0) _facing_direction = PlayerDirection::UP_RIGHT;
        else if(dx < 0 && dy > 0) _facing_direction = PlayerDirection::DOWN_LEFT;
        else if(dx > 0 && dy > 0) _facing_direction = PlayerDirection::DOWN_RIGHT;
        else if(dx < 0)           _facing_direction = PlayerDirection::LEFT;
        else if(dx > 0)           _facing_direction = PlayerDirection::RIGHT;
        else if(dy < 0)           _facing_direction = PlayerDirection::UP;
        else if(dy > 0)           _facing_direction = PlayerDirection::DOWN;
    }

    _sprite.set_x(_sprite.x() + dx);
    _sprite.set_y(_sprite.y() + dy);
}


void Player::handle_attack()
{
    if(_attack_timer > 0)
    {
        _attack_timer--;
        
        // TODO: Keep the sword hitbox active and process collisions
    }
    else
    {
        // Attack duration is over, return to idle state
        _state = PlayerState::IDLE;
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