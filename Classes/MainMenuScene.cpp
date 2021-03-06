#include "MainMenuScene.h"
#include "GameScene.h"
#include "Storage.h"
#include "AudioUtil.h"

#define MUTE "mute"
#define MUTE_BUTTON "mute.png"
#define UNMUTE_BUTTON "unmute.jpg"

Scene* MainMenuScene::_scene(nullptr);

Scene* MainMenuScene::getSceneInstance()
{
	if (!_scene) {
		_scene = Scene::create();
		auto layer = MainMenuScene::create();
		_scene->addChild(layer);
	}
	return _scene;
}


bool MainMenuScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	int midlX = origin.x + visibleSize.width / 2;

	auto label = Label::createWithBMFont("fonts/font.fnt", "Laser Game");
	label->setPosition(Vec2::ZERO);
	MenuItemLabel* menuLabel = MenuItemLabel::create(label);
	menuLabel->setDisabledColor(Color3B::WHITE);
	menuLabel->setEnabled(false);

	auto playItem = MenuItemImage::create(
		"play-button.png",
		"play-button.png",
		CC_CALLBACK_1 (MainMenuScene::play,this));


	playItem->setPosition(Vec2(0, -100));
	playItem->setScale(0.5);

	bool mute = Storage::getb(MUTE);
	string button;

	if (mute)
	{
		button = MUTE_BUTTON;
		AudioUtil::mute();
	}
	else
	{
		button = UNMUTE_BUTTON;
		AudioUtil::unmute();
	}

	_soundButton = MenuItemImage::create(
		button,
		button,
		CC_CALLBACK_1(MainMenuScene::sound, this)
		);
	_soundButton->setPosition(Vec2(0, -200));
	_soundButton->setScale(0.5);

	Vector<MenuItem*> menuItems;
	menuItems.pushBack(playItem);
	menuItems.pushBack(menuLabel);
	menuItems.pushBack(_soundButton);

	auto menu = Menu::createWithArray(menuItems);
	menu->setPosition(Point(midlX, origin.y + visibleSize.height / 2 + 100));
	addChild(menu, 1);

	_generator = Generator::create();
	addChild(_generator, 0);

	//add first lasers
	for (float dt = 0; dt < 5; dt++) {
		update(dt);
	}

	scheduleUpdate();
	AudioUtil::startLazerMoveBackground();
	return true;
}

void MainMenuScene::update(float dt)
{
	if (_generator->numLasers() < 10)
		_generator->addLaser();

	_generator->step(dt);
	_generator->render();
}

void MainMenuScene::play(Ref* ref)
{
	auto nextScene = GameScene::getSceneInstance();
	auto transition = TransitionFade::create(0.5, nextScene);
	Director::getInstance()->replaceScene(transition);
}

void MainMenuScene::sound(Ref* ref)
{
	bool mute = !Storage::getb(MUTE);
	string button;

	if (mute)
	{
		button = MUTE_BUTTON;
		AudioUtil::mute();
	}
	else
	{
		button = UNMUTE_BUTTON;
		AudioUtil::unmute();
	}

	_soundButton->setNormalImage(Sprite::create(button));
	_soundButton->setSelectedImage(Sprite::create(button));

	Storage::setb(MUTE, mute);
}
