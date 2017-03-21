#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "PhysicsShapeCache.h"
#include "Laser.h"
#include "Math.h"
#include "IOS"
#include "AudioUtil.h"

#define COCOS2D_DEBUG 1
#define PHYSICS_PLIST "physics.json.plist"
USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
    
	auto layer = GameScene::create();

    scene->addChild(layer, 0, "GameScene");

    return scene;
}

bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	PhysicsShapeCache::getInstance()->addShapesWithFile(PHYSICS_PLIST);

	_hero = Hero::create();
    this->addChild(_hero, 2);

    _generator = Generator::create();
	_generator->addLaser();
	this->addChild(_generator, 0);

	_gui = GameGUIFacade::create();
	this->addChild(_gui, 3);
	setScore(0);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	EventListenerTouchOneByOne* touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
	EventListenerMouse* mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(GameScene::onMouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
#endif


	AudioUtil::startLazerMoveBackground();

    return true;
}

void GameScene::onMouseDown(cocos2d::Event *event)
{
	if (!isRunning())
	{
		return;
	}
	EventMouse* e = (EventMouse*)event;
	_hero->jump(e->getLocationInView());
}

bool GameScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	if (!isRunning())
	{
		return true;
	}
	cocos2d::Vec2 to = touch->getLocationInView();
	reverse(to);
	_hero->jump(to);

	return true;
}

void GameScene::reverse(cocos2d::Vec2& vec)
{
	Size size = Director::getInstance()->getVisibleSize();
	vec.y = size.height - vec.y;
}

void GameScene::update(float dt)
{
	if (!isRunning()) 
	{
		return;
	}

	if (_generator->islaserHitHero())
	{
		_gui->showGameOverMenu(_score);
		this->_running = false;
	}

	if (_generator->numLasers() < 10 && _generator->timeFromLastLaser()>=1)
		_generator->addLaser();

	_generator->step(dt);
	_generator->render();
	if (!_hero->jumping())
		_generator->collideLasersVsHero();

	setScore(_score + dt);
}

void GameScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
	#endif
}

void GameScene::setScore(float score)
{
	_score = score;
	_gui->setScore(_score);
}

bool GameScene::isRunning()
{
	return _running;
}

void GameScene::setRunning(bool b)
{
	_generator->cleanLasers();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	_hero->jump(Vec2(visibleSize.width/2, visibleSize.height/2));
	_running = b;
	_generator->setLaserHitHero(!b);
	setScore(0);
}

void GameScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	this->scheduleUpdate();
}