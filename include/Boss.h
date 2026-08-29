#ifndef BOSS_H
#define BOSS_H

#include "bn_color.h"
#include "bn_vector.h"
#include "bn_fixed_rect.h"
#include "bn_unique_ptr.h"
#include "bn_fixed_point.h"

#include "bn_sprite_ptr.h"

class Boss {

public:
    virtual ~Boss() = default;


    [[nodiscard]] int life() const
    {
        return _life;
    }


protected:
    Boss(const bn::sprite_ptr& sprite);
    virtual void _update() = 0;

    [[nodiscard]] const bn::fixed_point& position() const
    {
        return _position;
    }

    [[nodiscard]] const bn::fixed_rect& hitbox() const
    {
        return _hitbox;
    }

private:
    int _life;
    bn::fixed_point _position;
    bn::fixed_rect _hitbox;

    bn::optional<bn::sprite_ptr> _bossSprite;
};

#endif