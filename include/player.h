#ifndef PLAYER_H
#define PLAYER_H

#include "bn_sprite_ptr.h"  // Allows us to create and manage the player's sprite
#include "bn_fixed_rect.h"  // Allows us to define the player's collision rectangle
#include "bn_optional.h"    // Allows us to create and destroy the sprite safely
#include "bn_fixed.h"       // Added for fixed-point math
#include "bn_sprite_animate_actions.h"

// Track the player's current action
enum class PlayerState {
    IDLE,
    MOVING,
    ATTACKING,
    KNOCKED_BACK,
    DASHING
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

    // Knockback tracking variables
    int _knockback_timer = 0;
    bn::fixed _knockback_dx = 0;
    bn::fixed _knockback_dy = 0;

    // Dash tracking variables
    int _dash_timer = 0;
    bn::fixed _dash_dx = 0;
    bn::fixed _dash_dy = 0;

    // Optional debug sprite that only exists when attacking
    bn::optional<bn::sprite_ptr> _debug_hitbox_sprite;
    bool _debug_hitbox_visible = false; // Track visibility of the debug hitbox sprite

    // Animations
    bn::sprite_animate_action<4> _anim_action;
    PlayerState _previous_state = PlayerState::IDLE;
    PlayerDirection _previous_direction = PlayerDirection::UP;



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

    bool is_attacking() const { return _state == PlayerState::ATTACKING; }

    // for triggering knockback
    void apply_knockback(bn::fixed dx, bn::fixed dy);

private:
    // Handles player movement based on input
    void handle_movement();

    // Handles player attacks and attack timing
    void handle_attack();

    // Handles invincibility frames and visual feedback
    void handle_invincibility();

    // Handles knockback logic
    void handle_knockback();

    // Handles dash logic
    void handle_dash();

    // Handles animation logic
    void update_animations();
};

#endif // PLAYER_H