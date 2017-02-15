#include "Generator.h"
#include "Math.h"
#include <vector>
#include <ctime>
#include "cocos2d.h"

Generator::Generator(int width, int height): 
_drawNode(cocos2d::DrawNode::create()),
_width (width), 
_height (height), 
_hWidth (width / 2), 
_hHeight (height / 2),
_radius(sqrt(width*width + height*height)), 
_diameter(_radius * 2), _velocity(120),
_lastLaserTime(0)
{
	
}

void Generator::addLaser()
{
	int side = ((double)rand() / RAND_MAX < 0.5) ? 1 : -1;
	float x(_hWidth - _radius + rand() * _diameter / RAND_MAX);
	float y(side * sqrt((_radius*_radius) - (x - _hWidth)*(x - _hWidth)) + _hHeight);
	float tox(_width - x);
	float toy(_height - y);
	float angle = M_PI_2 + atan2(-y + _hHeight, -x + _hWidth);
	Laser laser(x, y, tox, toy, _radius, angle);
	_lasers.push_back(laser);
	_lastLaserTime = std::time(0);
}

void Generator::step(float dt)
{
	std::vector<Laser> newLasers;
	for (std::vector<Laser>::iterator i = _lasers.begin(); i != _lasers.end(); ++i)
		if (i->step(dt, _velocity))
			newLasers.push_back(*i);
	_lasers = newLasers;
}

int Generator::timeFromLastLaser() const
{
	return std::time(0) - _lastLaserTime;
}

void Generator::render()
{
	_drawNode->clear();
	for (std::vector<Laser>::iterator i = _lasers.begin(); i != _lasers.end(); ++i)
		render(*i);
}

void Generator::render(Laser& l)
{
	_drawNode->drawSegment(cocos2d::Vec2(l.bx(), l.by()), 
						  cocos2d::Vec2(l.ax(), l.ay()), 
						  3.0f,
						  cocos2d::Color4F::RED);
}

Generator::~Generator()
{
}
