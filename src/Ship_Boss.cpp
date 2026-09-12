#include "Ship_Boss.h"

#include "Bullet.h"
#include "MapManager.h"

ShipBoss::ShipBoss(bn::sprite_ptr sprite, bn::camera_ptr camera)
    : Boss(sprite,camera)
{

    _life = 50;
    _position.set_x(60);
    _position.set_y(60);
}

void ShipBoss::Update()
{
    Boss::Update();

    bn::vector<bn::unique_ptr<Bullet>, 10>::iterator it = _activeBullets.begin();
    while (it != _activeBullets.end())
    {
        bn::unique_ptr<Bullet> &bullet = *it;

        // Update the bullet
        bullet->Update();

        // Check if it's off-screen and erase it, otherwise advance the iterator
        if (bullet->IsOffScreen())
        {
            it = _activeBullets.erase(it);
        }
        else
        {
            ++it;
        }
    }

    if (_life == 0)
    {
        return;
    }

    switch (_state)
    {
    case state::IDLE:
        HandleIdleState();
        break;
    case state::MOVE:
        HandleMoveState();
        break;
    case state::ATTACK:
        HandleAttackState();
        break;
    default:
        break;
    }

    HandleImmuneState();
}

void ShipBoss::TakeDamage(int damage)
{

    if (_immuneFrames == 0)
    {
        Boss::TakeDamage(damage);
        _immuneFrames = 18;
    }
}

void ShipBoss::TransitionToState(state newState)
{
    _state = newState;
    _stateTimer = 0; // Reset timer on state entry

    switch (_state)
    {
    case state::IDLE:

        break;
    case state::MOVE:
        SetRandomDestination();
        break;
    case state::ATTACK:
        _bulletsFired = 0;
        _shotTimer = 0;
        break;
    default:
        break;
    }
}

void ShipBoss::HandleIdleState()
{
    _stateTimer += 1;

    if (_stateTimer >= _idleDuration)
    {
        // Randomly choose between MOVE and ATTACK after idling
        if (_random.get() < 0x7FFFFFFF)
            TransitionToState(state::MOVE);
        else
            TransitionToState(state::ATTACK);
    }
}

void ShipBoss::SetRandomDestination()
{
    bn::fixed randomX = _random.get_fixed(-80, 80);
    bn::fixed randomY = _random.get_fixed(-60,60);

    _targetPosition.set_x(randomX);
    _targetPosition.set_y(randomY);
}

void ShipBoss::HandleMoveState()
{
    bn::fixed dx = _targetPosition.x() - _position.x();
    bn::fixed dy = _targetPosition.y() - _position.y();
    bn::fixed distance = bn::sqrt((dx * dx) + (dy * dy));

    if (distance <= _speed)
    {
        _position = _targetPosition;
        TransitionToState(state::IDLE);
    }
    else
    {
        _position.set_x(_position.x() + (dx / distance) * _speed);
        _position.set_y(_position.y() + (dy / distance) * _speed);
    }
}

void ShipBoss::HandleAttackState()
{

    _shotTimer += 1;

    if (_shotTimer >= _timeBetweenShots && _bulletsFired < _bulletsPerAttack)
    {
        Shoot();

        _bulletsFired++;
        _shotTimer = 0; // Reset fire timer for the next bullet
    }

    // Once all bullets are fired, handle attack cooldown before switching states
    if (_bulletsFired >= _bulletsPerAttack)
    {
        _stateTimer += 1;
        if (_stateTimer >= _attackCooldown)
        {
            TransitionToState(state::MOVE);
        }
    }
}

void ShipBoss::Shoot()
{
    bn::fixed_point bulletDirection(_random.get_fixed(-1, 1), _random.get_fixed(-1, 1));

    _activeBullets.push_back(bn::make_unique<Bullet>(
        bn::sprite_items::bullet.create_sprite(_position.x(), _position.y()),
        bulletDirection,
        2, _camera));
}

void ShipBoss::HandleImmuneState()
{
    if (_immuneFrames > 0)
    {
        _immuneFrames--;
        _bossSprite.set_visible(_immuneFrames % 4 != 0);
    }
    else
    {
        _bossSprite.set_visible(true);
    }
}