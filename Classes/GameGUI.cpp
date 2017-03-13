#include "GameGUI.h"
#include <sstream>

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()


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

	_gameOverMenu = GameOverMenu::create();
	this->addChild(_gameOverMenu, 2);

	return true;
}

void GameGUI::setScore(int score)
{
	_score->setString(SSTR(score));
}

void GameGUI::showGameOverMenu()
{
	_gameOverMenu->show();
}

