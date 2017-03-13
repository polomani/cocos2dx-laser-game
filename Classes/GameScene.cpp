#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "PhysicsShapeCache.h"
#include "Laser.h"
#include "Hero.h"
#include "GameGUI.h"
#include "Math.h"
#include "IOS"

#define COCOS2D_DEBUG 1
#define PHYSICS_PLIST "physics.json.plist"
USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
    
    // 'layer' is an autorelease object
	auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer, 0, "GameScene");

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
										   CC_CALLBACK_1(GameScene::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...
	PhysicsShapeCache::getInstance()->addShapesWithFile(PHYSICS_PLIST);

	_hero = Hero::create();
    this->addChild(_hero, 2);

    _generator = Generator::create();
	_generator->addLaser();
	this->addChild(_generator, 0);

	_gui = GameGUI::create();
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

	// to run onUpdate() method
	this->scheduleUpdate();
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
		_gui->showGameOverMenu();
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
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
	#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
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