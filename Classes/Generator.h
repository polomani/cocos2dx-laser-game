#ifndef __GENERATOR_H__
#define __GENERATOR_H__

#include "Laser.h"
#include <vector>
#include <ctime>
#include "cocos2d.h"

class Generator
{
private:
	cocos2d::DrawNode* _drawNode;
	int _hWidth, _hHeight, _width, _height;
	float _radius, _diameter, _velocity;
	std::time_t _lastLaserTime;
	std::vector<Laser> _lasers;
	void render(Laser& laser);
public:
	void step(float dt);
	int timeFromLastLaser() const;
	int numLasers() const { return _lasers.size(); };
	void render();
	Generator(int width, int height);
	cocos2d::DrawNode* drawNode() const { return _drawNode; };
	void addLaser();
	~Generator();
};

#endif // __GENERATOR_H__
