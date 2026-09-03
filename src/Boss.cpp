#include "Boss.h"

Boss::Boss(bn::sprite_ptr sprite)
    :  _bossSpritePtr(sprite)
{

}

void Boss::Update()
{
    bossSprite()->set_x(_position.x());
    bossSprite()->set_y(_position.y());
}

void Boss::SetState(state toSetTo)
{
    _state = toSetTo;
}