#include "GameScene.h"
#include "AudioUtil.h"
#include "Storage.h"

using namespace cocos2d;

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

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

	Label* _label = Label::createWithBMFont("fonts/font.fnt", "Game Over");
	_label->setPosition(Vec2(0, 100));
	MenuItemLabel* menuLabel = MenuItemLabel::create(_label);
	menuLabel->setDisabledColor(Color3B::WHITE);
	menuLabel->setEnabled(false);

	_label = Label::createWithBMFont("fonts/font.fnt", "Current points is: 0");
	_label->setPosition(Vec2(0, 0));
	_currentPointsLabel = MenuItemLabel::create(_label);
	_currentPointsLabel->setDisabledColor(Color3B::WHITE);
	_currentPointsLabel->setEnabled(false);

	_label = Label::createWithBMFont("fonts/font.fnt", "No records");
	_label->setPosition(Vec2(0, -100));
	_recordLabel = MenuItemLabel::create(_label);
	_recordLabel->setDisabledColor(Color3B::WHITE);
	_recordLabel->setEnabled(false);

	auto closeItem = MenuItemImage::create(
		"restart-button.png",
		"restart-button.png",
		CC_CALLBACK_1(GameOverMenu::menuRestartClick, this));

	closeItem->setPosition(Vec2(0, -200));
	closeItem->setScale(0.5);

	Vector<MenuItem*> menuItems;
	menuItems.pushBack(closeItem);
	menuItems.pushBack(menuLabel);
	menuItems.pushBack(_recordLabel);
	menuItems.pushBack(_currentPointsLabel);

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

void GameOverMenu::show(int score)
{
	_currentPointsLabel->setString("Score: " + SSTR(score));

	int record = Storage::geti("record");
	_recordLabel->setString("Best: " + SSTR(record));
	_recordLabel->setVisible(record > 0);

	if (score > record)
	{
		Storage::seti("record", score);
		_recordLabel->setString("NEW Best: " + SSTR(record));
	}

	setVisible(true);
}

void GameOverMenu::menuRestartClick(Ref* pSender)
{
	GameScene* scene = (GameScene*) Director::getInstance()->getRunningScene()->getChildByName("GameScene");
	scene->setRunning(true);
	setVisible(false);
	AudioUtil::startLazerMoveBackground();
}