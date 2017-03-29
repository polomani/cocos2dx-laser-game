#include "HUD.h"
#include <sstream>
#include "cocos2d.h"
#include "GameGUIFacade.h"
#include "GameScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

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

	auto pauseButton = MenuItemImage::create(
		"pause-button.png",
		"pause-button.png");

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	EventListenerTouchOneByOne* touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [](Touch* touch, Event* event) { 
		GameGUIFacade::getInstance()->showPauseWindowTouch(touch, event); 
		return true; 
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, pauseButton);
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
	EventListenerMouse* clickListener = EventListenerMouse::create();
	clickListener->onMouseDown = [](Event* event) { GameGUIFacade::getInstance()->showPauseWindowClick(event); };
	_eventDispatcher->addEventListenerWithSceneGraphPriority(clickListener, pauseButton);
#endif


	pauseButton->setScale(0.1);
	pauseButton->setPosition(Vec2(origin.x + visibleSize.width - pauseButton->getContentSize().width * pauseButton->getScale() / 2,
		origin.y + pauseButton->getContentSize().height * pauseButton->getScale() / 2));

	auto menu = Menu::create(pauseButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 5);

	return true;
}

void HudMenu::setScore(int score)
{
	_score->setString(SSTR(score));
}
