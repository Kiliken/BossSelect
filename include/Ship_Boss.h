#ifndef SHIP_BOSS_H
#define SHIP_BOSS_H

#include "Boss.h"

class ShipBoss : public Boss {

public:
    ShipBoss(const bn::sprite_ptr& sprite);
    ~ShipBoss();

private:
    void _update() override;
};

#endif