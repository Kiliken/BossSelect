#include "Boss.h"

Boss::Boss(bn::sprite_ptr sprite, bn::camera_ptr camera)
    :  _bossSprite(sprite), _camera(camera)
{
    _bossSprite.set_camera(camera);
    _hitbox = bn::fixed_rect{0,0,16,16};
}

void Boss::Update()
{
    _bossSprite.set_x(_position.x());
    _bossSprite.set_y(_position.y());

    _hitbox.set_position(_position.x(), _position.y());

    if(_life == 0){
        _bossSprite.set_visible(false);
        return;
    }
}

void Boss::SetState(state toSetTo)
{
    _state = toSetTo;
}

void Boss::TakeDamage(int damage)
{
    _life -= (damage <= _life ? damage : 0);
}