#include "MainMenuScene.h"
#include "GameScene.h"


Scene* MainMenuScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainMenuScene::create();
	scene->addChild(layer);
	return scene;
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

	Vector<MenuItem*> menuItems;
	menuItems.pushBack(playItem);
	menuItems.pushBack(menuLabel);

	auto menu = Menu::createWithArray(menuItems);
	menu->setPosition(Point(midlX, origin.y + visibleSize.height / 2 + 100));
	this->addChild(menu, 1);

	_generator = Generator::create();
	_generator->addLaser();
	this->addChild(_generator, 0);

	//add first lasers
	for (float dt = 0; dt < 5; dt++)
		update(dt);

	this->scheduleUpdate();

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
	auto nextScene = GameScene::createScene();
	auto transition = TransitionFade::create(0.5, nextScene);
	Director::getInstance()->replaceScene(transition);
}