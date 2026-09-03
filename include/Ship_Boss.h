#ifndef SHIP_BOSS_H
#define SHIP_BOSS_H

#include "Boss.h"

class ShipBoss : Boss {

public:
    ShipBoss(bn::sprite_ptr sprite);
    ~ShipBoss() override = default;

    void Update() override;
private:
    

    // States related
    void TransitionToState(state newState);
    void HandleIdleState();
    void HandleMoveState();
    void HandleAttackState();


    void SetRandomDestination();


    // Variables

    // State
    uint32_t _stateTimer = 0;
    uint32_t _idleDuration = 360;
    bn::random _random;

    // Position
    bn::fixed_point _targetPosition;
    bn::fixed _speed = 2;

    // Attack
    uint32_t _shotTimer = 0;
    uint32_t _attackCooldown = 360;
    uint32_t _timeBetweenShots = 120;
    int _bulletsFired = 0;
    int _bulletsPerAttack = 0;
};

#endif