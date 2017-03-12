#include "GameOverMenu.h"

#include "HelloWorldScene.h"

using namespace cocos2d;

GameOverMenu::GameOverMenu()
{
	// by default menu should be hidden
	setVisible(false);
	
}

bool GameOverMenu::init()
{
	if (!LayerColor::initWithColor(Color4B(144, 144, 144, 100)))
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	int midlX = origin.x + visibleSize.width / 2;

	Label* _label = Label::createWithTTF("Game Over", "fonts/Marker Felt.ttf", 40);
	_label->setPosition(Vec2::ZERO);
	MenuItemLabel* menuLabel = MenuItemLabel::create(_label);

	auto closeItem = MenuItemImage::create(
		"restart-button.png",
		"restart-button.png",
		CC_CALLBACK_1(GameOverMenu::menuRestartClick, this));

	closeItem->setPosition(Vec2(0, -100));
	closeItem->setScale(0.5);

	Vector<MenuItem*> menuItems;
	menuItems.pushBack(closeItem);
	menuItems.pushBack(menuLabel);

	auto menu = Menu::createWithArray(menuItems);
	menu->setPosition(
		Point(
			midlX,
			origin.y + visibleSize.height / 2 + 100
		)
	);
	this->addChild(menu, 1);

	return true;
}

void GameOverMenu::show()
{
	setVisible(true);
}

void GameOverMenu::menuRestartClick(Ref* pSender)
{
	_gameScene->setRunning(true);
	setVisible(false);
}