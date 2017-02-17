#include "Laser.h"
#include "Math.h"
#include "cocos2d.h"

#define COCOS2D_DEBUG 1

float random(int min, int max)
{
	return (float)min + (rand() % (int)(max - min + 1));
}

Laser::Laser(float x, float y, float tox, float toy, float radius, float angle) :
_x(x), 
_y(y), 
_angle(angle), 
_tox(tox), 
_toy(toy), 
_direction(_tox - _x, _toy - _y),
_dx(radius * cos(angle)), _dy(radius * sin(angle)),
_alpha(1 / random(1, 4)), _r(1 / random(1, 10)), _g(1 / random(1, 10)), _b(1 / random(1, 10))
{
	_direction.normalize();
}

cocos2d::GLProgramState* Laser::getState(cocos2d::GLProgram* program)
{
	cocos2d::GLProgramState* state = cocos2d::GLProgramState::getOrCreateWithGLProgram(program);

	// name of paramert in lazer vertex shader
	state->setUniformVec4("lazer_color", cocos2d::Vec4(_r, _g, _b, _alpha));
	return state;
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
