#include "GameGUI.h"




bool GameGUI::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_score = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 32);
	_score->setPosition(Point(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - _score->getBoundingBox().size.height));
	this->addChild(_score, 1);

	return true;
}

void GameGUI::setScore(int score)
{
	_score->setString(std::to_string(score));
}

