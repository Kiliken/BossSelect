#ifndef SHIP_BOSS_H
#define SHIP_BOSS_H

#include "Boss.h"

class ShipBoss : Boss {

public:
    ShipBoss(const bn::sprite_ptr& sprite);
    ~ShipBoss();

private:
    void Update() override;
};

#endif