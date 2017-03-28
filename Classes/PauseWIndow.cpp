#include "PauseWindow.h"
#include "GameScene.h"

PauseWindow::PauseWindow():_paused(false)
{
	setVisible(false);
}

bool PauseWindow::init() {
	if (!LayerColor::initWithColor(Color4B(144, 144, 144, 100)))
	{
		return false;
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	EventListenerTouchOneByOne* touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(PauseWindow::pauseTapCallBack, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
	EventListenerMouse* mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(PauseWindow::pauseClickCallBack, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
#endif

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto label = Label::createWithBMFont("fonts/font.fnt", "Tap to continue");
	label->setPosition(Point(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height/2));
	this->addChild(label, 1);

	return true;
}

void PauseWindow::show() {
	Director::getInstance()->pause();
	GameScene* gameScene = dynamic_cast<GameScene*> (Director::getInstance()->getRunningScene()->getChildByName("GameScene"));
	if (gameScene && gameScene->isRunning()) {
		setVisible(true);
	}
	paused(true);
}

void PauseWindow::close() {
	Director::getInstance()->resume();
	setVisible(false);
	paused(false);
}

void PauseWindow::pauseClickCallBack(Event* event)
{
	if (paused()) {
		event->stopPropagation();
		close();
	}
}

bool PauseWindow::pauseTapCallBack(Touch* touch, Event* event)
{
	if (paused()) {
		event->stopPropagation();
		close();
	}
	return true;
}