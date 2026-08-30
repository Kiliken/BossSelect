#include "Ship_Boss.h"

ShipBoss::ShipBoss(const bn::sprite_ptr& sprite)
 : Boss(sprite){
    
}

void ShipBoss::Update() {
    switch (getState())
    {
    case state::IDLE:
        break;

    default:
        break;
    }
}