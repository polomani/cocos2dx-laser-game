#include "GameGUIFacade.h"
#include "PauseWindow.h"
#include <sstream>

#define COCOS2D_DEBUG 1

bool GameGUIFacade::init()
{
	if (!Layer::init())
	{
		return false;
	}

	_hudMenu = HudMenu::create(this);
	this->addChild(_hudMenu, 4);

	_gameOverMenu = GameOverMenu::create();
	this->addChild(_gameOverMenu, 5);

	_pauseWindow = PauseWindow::create();
	this->addChild(_pauseWindow, 6);

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

void GameGUIFacade::showPauseWindowClick(Event* event)
{
	EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
	auto bounds = mouseEvent->getCurrentTarget()->getBoundingBox();
	if (bounds.containsPoint(mouseEvent->getLocationInView())) {
		_pauseWindow->show();
		event->stopPropagation();
	}
}

bool GameGUIFacade::showPauseWindowTouch(Touch* touch, Event* event)
{
	auto bounds = event->getCurrentTarget()->getBoundingBox();
	if (bounds.containsPoint(touch->getLocationInView())) {
		_pauseWindow->show();
		event->stopPropagation();
	}
	return true;
}

void GameGUIFacade::closePauseWindow(Event* event)
{
	event->stopPropagation();
	_pauseWindow->close();
}
