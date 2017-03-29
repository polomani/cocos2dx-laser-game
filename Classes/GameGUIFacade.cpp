#include "GameGUIFacade.h"
#include "PauseWindow.h"
#include "GameScene.h"
#include <sstream>

#define COCOS2D_DEBUG 1

GameGUIFacade* GameGUIFacade::_gui(nullptr);

GameGUIFacade* GameGUIFacade::getInstance() {
	if (!_gui)
		_gui = GameGUIFacade::create();

	return _gui;
}

bool GameGUIFacade::init()
{
	if (!Layer::init())
	{
		return false;
	}

	_hudMenu = HudMenu::create();
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

void GameGUIFacade::showPauseWindow()
{
	_pauseWindow->show();
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
	Vec2 vec = touch->getLocationInView();
	GameScene::reverse(vec);
	if (bounds.containsPoint(vec)) {
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
