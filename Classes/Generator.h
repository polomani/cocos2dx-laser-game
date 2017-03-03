#ifndef __GENERATOR_H__
#define __GENERATOR_H__

#include "Laser.h"
#include <vector>
#include <ctime>
#include "cocos2d.h"

class Generator : public cocos2d::DrawNode
{
private:
	int _width, _height, _hWidth, _hHeight;
	float _radius, _diameter, _velocity;
	std::time_t _lastLaserTime;
	std::vector<Laser> _lasers;
	void render(Laser& laser);
	
	cocos2d::GLProgram* _shaderProgram;
	cocos2d::Vec4 _lazerColor;

	void generateLazerColor();

public:
	// constructor will be invoked by create function
	Generator();
	CREATE_FUNC(Generator);

	virtual bool init();

	void step(float dt);
	int timeFromLastLaser() const;
	int numLasers() const { return _lasers.size(); };
	void render();
	void collideLasersVsHero();
	void addLaser();
};

#endif // __GENERATOR_H__
