#include "Boss.h"

Boss::Boss(bn::sprite_ptr sprite)
    :  _bossSprite(sprite)
{

}

void Boss::Update()
{
    _bossSprite.set_x(_position.x());
    _bossSprite.set_y(_position.y());
}

void Boss::SetState(state toSetTo)
{
    _state = toSetTo;
}