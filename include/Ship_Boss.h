#ifndef SHIP_BOSS_H
#define SHIP_BOSS_H

#include "Boss.h"



// Forward declarations
class Bullet;
class MapManager;

class ShipBoss : public Boss {

public:
    ShipBoss(bn::sprite_ptr sprite, bn::camera_ptr camera);
    ~ShipBoss() override = default;

    void Update() override;
    void TakeDamage(int damage) override;
private:
    

    // States related
    void TransitionToState(state newState);
    void HandleIdleState();
    void HandleMoveState();
    void HandleAttackState();
    void HandleImmuneState();

    void Shoot();

    void SetRandomDestination();


    // Variables

    // State
    uint32_t _stateTimer = 0;
    uint32_t _idleDuration = 30;
    bn::random _random;

    // Position
    bn::fixed_point _targetPosition;
    bn::fixed _speed = 2;
    MapManager* _map;

    // Attack
    uint32_t _shotTimer = 0;
    uint32_t _attackCooldown = 30;
    uint32_t _timeBetweenShots = 20;
    int _bulletsFired = 0;
    int _bulletsPerAttack = 7;
    u_int32_t _immuneFrames = 0;

    bn::vector<bn::unique_ptr<Bullet>, 10> _activeBullets;
};

#endif