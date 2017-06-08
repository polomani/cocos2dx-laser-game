#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "PhysicsShapeCache.h"
#include "Laser.h"
#include "Math.h"
#include "IOS"
#include "AudioUtil.h"
#include "Static.h"

#define PHYSICS_PLIST "physics.json.plist"

Scene* GameScene::_scene(0);

Scene* GameScene::getSceneInstance()
{
	if (!_scene) {
		_scene = Scene::createWithPhysics();
		auto layer = GameScene::create();
		_scene->addChild(layer, 0, 0);
	}

    return _scene;
}

GameScene* GameScene::getInstance()
{
	if (_scene)
		return dynamic_cast<GameScene*>  (getSceneInstance()->getChildByTag(0));
	return nullptr;
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
    addChild(_hero, 2);

    _generator = Generator::create();
	addChild(_generator, 0);

	_gui = GameGUIFacade::getInstance();
	addChild(_gui, 3);

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

    return true;
}

void GameScene::onMouseDown(Event *event)
{
	if (!isRunning())
	{
		return;
	}
	EventMouse* e = (EventMouse*)event;
	_hero->jump(e->getLocationInView());
}

bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
	if (!isRunning())
	{
		return true;
	}
	Vec2 to = touch->getLocationInView();
	reverse(to);
	_hero->jump(to);

	return true;
}

void GameScene::reverse(Vec2& vec)
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

	if (_generator->numLasers() < 20 && _generator->timeFromLastLaser() >= 1)
		_generator->addLaser();

	_generator->step(dt);
	_generator->render();
	if (!_hero->jumping())
		_generator->collideLasersVsHero();

	setScore(_score + dt);
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

void GameScene::gameOver()
{
	_gui->showGameOverMenu(_score);
	_running = false;
	AudioUtil::laserHitEffect();
	AudioUtil::endLazerMoveBackground();
	AudioUtil::gameOverPlayground();
}

void GameScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	startGame();
	scheduleUpdate();
}

void GameScene::startGame()
{
	_generator->cleanLasers();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	_hero->jump(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	_running = true;

	for (float dt = 0; dt < 2.5; dt+=0.5)
	{
		_generator->addLaser();
		update(dt);
	}
	
	setScore(0);
	AudioUtil::startLazerMoveBackground();
}