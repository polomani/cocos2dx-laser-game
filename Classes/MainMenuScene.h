#ifndef __MAIN_MENU_SCENE__
#define __MAIN_MENU_SCENE__

#include "cocos2d.h"
#include "Generator.h"

USING_NS_CC;

class MainMenuScene: public Layer
{
	Generator* _generator;

	MenuItemImage* _soundButton;
public:
	static Scene* createScene();
	virtual bool init();
	virtual void update(float);
	CREATE_FUNC(MainMenuScene);
	void play(Ref*);
	void sound(Ref*);
};

#endif //__MAIN_MENU_SCENE__

