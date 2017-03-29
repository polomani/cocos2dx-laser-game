#ifndef __MAIN_MENU_SCENE__
#define __MAIN_MENU_SCENE__

#include "Static.h"
#include "Generator.h"


class MainMenuScene: public Layer
{
	static Scene* _scene;

	Generator* _generator;

	MenuItemImage* _soundButton;

	CREATE_FUNC(MainMenuScene);
public:
	static Scene* getSceneInstance();
	virtual bool init();
	virtual void update(float);
	void play(Ref*);
	void sound(Ref*);
};

#endif //__MAIN_MENU_SCENE__

