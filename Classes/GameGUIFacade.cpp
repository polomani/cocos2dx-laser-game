#include "GameGUIFacade.h"
#include <sstream>

bool GameGUIFacade::init()
{
	if (!Layer::init())
	{
		return false;
	}

	_hudMenu = HudMenu::create();
	this->addChild(_hudMenu, 1);

	_gameOverMenu = GameOverMenu::create();
	this->addChild(_gameOverMenu, 5);

	return true;
}

void GameGUIFacade::setScore(int score)
{
	_hudMenu->setScore(score);
}

void GameGUIFacade::showGameOverMenu(int score)
{
	_gameOverMenu->show(score);
}

