#ifndef __LASER_H__
#define __LASER_H__

#include "cocos2d.h"

class Laser
{
private:
	float _x, _y, _dx, _dy, _tox, _toy;
	cocos2d::Vec2 _direction;
	float _angle;
public:
	Laser(float x, float y, float tox, float toy, float radius, float angle);
	~Laser();
	bool step(float dt, float velocity);
	float x() const { return _x; }
	float y() const { return _y; }
	float tox() const { return _tox; };
	float toy() const { return _toy; };
	float ax() const { return _x + _dx; };
	float ay() const { return _y + _dy; };
	float bx() const { return _x - _dx; };
	float by() const { return _y - _dy; };
	float dx() const { return _dx; };
	float dy() const { return _dy; };
	void x(float x) { _x = x; };
	void y(float y) { _y = y; };
};

#endif // __LASER_H__
