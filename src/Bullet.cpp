#include "Bullet.h"

Bullet::Bullet(bn::sprite_ptr sprite, bn::fixed_point direction, bn::fixed speed)
    : _sprite(sprite), _direction(direction), _speed(speed)
{
}

void Bullet::Update()
{
    // Move the bullet in the specified direction
    _sprite.set_position(_sprite.position() + utils::fixed::normalize(_direction) * _speed);
}

bool Bullet::IsOffScreen() const
{
    // Check if the bullet is outside the screen bounds
    return _sprite.x() < -120 || _sprite.x() > 120 || _sprite.y() < -80 || _sprite.y() > 80;
}

bn::fixed_rect Bullet::GetCollisionRect() const
{
    return _collisionRect;
}

