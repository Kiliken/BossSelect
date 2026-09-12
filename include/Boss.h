#ifndef BOSS_H
#define BOSS_H

#include "bn_color.h"
#include "bn_vector.h"
#include "bn_fixed_rect.h"
#include "bn_unique_ptr.h"
#include "bn_fixed_point.h"
#include "bn_random.h"

#include "bn_sprite_ptr.h"

#include "bn_sprite_items_bullet.h"
#include "bn_camera_ptr.h"

#include "utils.h"

class Boss
{

public:
    enum class state
    {
        IDLE,
        MOVE,
        ATTACK
    };

    virtual ~Boss() = default;

    [[nodiscard]] int life() const
    {
        return _life;
    }

    [[nodiscard]] const bn::fixed_point &position() const
    {
        return _position;
    }

    [[nodiscard]] const bn::fixed_rect &hitbox() const
    {
        return _hitbox;
    }

    [[nodiscard]] state getState() const
    {
        return _state;
    }

    void SetState(state toSetTo);

protected:
    Boss(bn::sprite_ptr sprite, bn::camera_ptr camera);
    virtual void Update() = 0;

    virtual void TakeDamage(int damage) = 0;

    state _state = state::IDLE;

    int _life;
    bn::fixed_point _position;
    bn::fixed_rect _hitbox;

    bn::sprite_ptr _bossSprite;
    bn::camera_ptr _camera;

private:
};

#endif