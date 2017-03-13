#include "HUD.h"
#include <sstream>

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

bool HudMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_score = Label::createWithBMFont("fonts/font.fnt", "0");
	_score->setPosition(Point(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - _score->getBoundingBox().size.height / 2));
	this->addChild(_score, 1);

	return true;
}

void HudMenu::setScore(int score)
{
	_score->setString(SSTR(score));
}
