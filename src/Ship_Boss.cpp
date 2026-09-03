#include "Ship_Boss.h"

ShipBoss::ShipBoss(bn::sprite_ptr sprite)
    : Boss(sprite)
{
}

void ShipBoss::Update()
{
    Boss::Update();

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
    bn::fixed randomX = _random.get_fixed(-80,80);
    bn::fixed randomY = _random.get_fixed(-80,80);

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
        // Shoot();
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