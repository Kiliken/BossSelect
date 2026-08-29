#ifndef PLAYER_H
#define PLAYER_H

#include "bn_sprite_ptr.h"
#include "bn_fixed_rect.h"

// Track the player's current action
enum class PlayerState {
    IDLE,
    MOVING,
    ATTACKING
};

// Track the 8-way movement facing direction
enum class PlayerDirection {
    UP, DOWN, LEFT, RIGHT,
    UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT
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

public:
    Player(int start_x, int start_y);

    void update();
    void take_damage(int amount);
    int get_hp() const;

    bn::fixed_rect get_collision_rect() const;

private:
    void handle_movement();
    void handle_attack();
    void handle_invincibility();
};

#endif // PLAYER_H