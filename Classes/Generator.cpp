#include "Generator.h"
#include "Math.h"
#include <vector>
#include <ctime>
#include "cocos2d.h"
#include "ShaderUtil.h"

using namespace cocos2d;

const char* Generator::vertexShader = "attribute vec4 a_position;attribute vec2 a_texCoord;attribute vec4 a_color;uniform vec4 lazer_color;\n #ifdef GL_ES \n varying lowp vec4 v_fragmentColor;varying mediump vec2 v_texCoord;varying mediump vec2 v_texCoord2;\n #else \n varying vec4 v_fragmentColor;varying vec2 v_texCoord;varying float v_screenY; \n #endif \n void main(){float alpha = 1.0;if (CC_Random01[0] < 0.5)alpha = 0.0;float blueshade = 1.0;v_fragmentColor = lazer_color;v_texCoord = a_texCoord;gl_Position = CC_MVPMatrix * a_position;v_screenY = gl_Position.y;}";
const char* Generator::fragmentShader = "#ifdef GL_ES \n varying lowp vec4 v_fragmentColor;varying mediump vec2 v_texCoord;varying mediump vec2 v_screenY; \n #else \n varying vec4 v_fragmentColor;varying vec2 v_texCoord;varying float v_screenY; \n #endif \n void main(){vec4 texColor = v_fragmentColor;if (texColor.a < 0.2)discard;if (mod(v_screenY + CC_SinTime[1], 0.005) > 0.0025)discard;gl_FragColor = vec4(texColor.xyz, 0.2);}";

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
	_shaderProgram(ShaderUtil::loadShaderFromStrings("lazer_shader", vertexShader, fragmentShader))
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
