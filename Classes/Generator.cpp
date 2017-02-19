#include "Generator.h"
#include "Math.h"
#include <vector>
#include <ctime>
#include "cocos2d.h"
#include "ShaderUtil.h"

using namespace cocos2d;

Generator::Generator()
	:
	_width(Director::getInstance()->getVisibleSize().width),
	_height(Director::getInstance()->getVisibleSize().height),
	_hWidth(_width / 2),
	_hHeight(_height / 2),
	_radius(sqrt(_width*_width + _height*_height)),
	_diameter(_radius * 2),
	_velocity(120),
	_lastLaserTime(0),
	_shaderProgram(ShaderUtil::loadShader("lazer_shader", "shaders/lazer", "shaders/lazer"))
{ }

bool Generator::init()
{
	if (!DrawNode::init())
	{
		return false;
	}

	if (!_shaderProgram)
		return false;

	setGLProgram(_shaderProgram);

	// initialize was successful
	return true;
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
	clear();
	for (std::vector<Laser>::iterator i = _lasers.begin(); i != _lasers.end(); ++i)
		render(*i);
}

void Generator::render(Laser& l)
{
	drawSegment(cocos2d::Vec2(l.bx(), l.by()), 
						  cocos2d::Vec2(l.ax(), l.ay()), 
						  3.0f,
						  cocos2d::Color4F::RED);
	
	setGLProgramState(l.getState(_shaderProgram));
	_shaderProgram->use();
}
