#ifndef BULLET_H
#define BULLET_H

#include "bn_color.h"
#include "bn_vector.h"
#include "bn_fixed_rect.h"
#include "bn_unique_ptr.h"
#include "bn_fixed_point.h"
#include "bn_random.h"

#include "bn_sprite_ptr.h"

#include "utils.h"

class Bullet {
public:
    Bullet(bn::sprite_ptr sprite, bn::fixed_point direction, bn::fixed speed);
    ~Bullet() = default;

    void Update();
    bool IsOffScreen() const;
    bn::fixed_rect GetCollisionRect() const;

private:
    bn::sprite_ptr _sprite;
    bn::fixed_point _direction;
    bn::fixed _speed;
    bn::fixed_rect _collisionRect;
};

#endif // BULLET_H