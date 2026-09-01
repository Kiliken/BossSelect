#ifndef PLAYER_H
#define PLAYER_H

#include "bn_sprite_ptr.h"  // Allows us to create and manage the player's sprite
#include "bn_fixed_rect.h"  // Allows us to define the player's collision rectangle
#include "bn_optional.h"    // Allows us to create and destroy the sprite safely

// Track the player's current action
enum class PlayerState {
    IDLE,
    MOVING,
    ATTACKING
};

// Track the movement facing direction
enum class PlayerDirection {
    UP, DOWN, LEFT, RIGHT
};

class Player 
{
private:
    bn::sprite_ptr _sprite;
    int _hp = 12;                 
    int _invincibility_frames = 0; 

    PlayerState _state = PlayerState::IDLE;
    PlayerDirection _facing_direction = PlayerDirection::DOWN;
    int _attack_timer = 0; // Counts down the frames of the attack

    // Optional debug sprite that only exists when attacking
    bn::optional<bn::sprite_ptr> _debug_hitbox_sprite;

public:
    Player(int start_x, int start_y);

    void update();
    
    // Handles taking damage and invincibility frames
    void take_damage(int amount);

    // Returns the player's current HP
    int get_hp() const;

    // Gets the collision rectangle for the player, used for collision detection
    bn::fixed_rect get_collision_rect() const;

    // Gets the collision rectangle for the player's sword attack, used for collision detection
    bn::fixed_rect get_sword_hitbox() const;

private:
    // Handles player movement based on input
    void handle_movement();

    // Handles player attacks and attack timing
    void handle_attack();

    // Handles invincibility frames and visual feedback
    void handle_invincibility();
};

#endif // PLAYER_H