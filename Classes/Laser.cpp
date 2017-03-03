#include "Laser.h"
#include "Math.h"
#include "cocos2d.h"

#define COCOS2D_DEBUG 1

Laser::Laser(float x, float y, float tox, float toy, float radius, float angle) :
_x(x), 
_y(y), 
_angle(angle), 
_tox(tox), 
_toy(toy), 
_direction(_tox - _x, _toy - _y),
_dx(radius * cos(angle)), _dy(radius * sin(angle))
{
	_direction.normalize();
}

bool Laser::step(float dt, float velocity)
{
	if (abs(_x - _tox) >= 1 || abs(_y - _toy) >= 1) {
		_x += _direction.x * velocity * dt;
		_y += _direction.y * velocity * dt;
		return true;
	}
	return false;
}

Laser::~Laser()
{
}
