#ifndef __MAIN_MENU_SCENE__
#define __MAIN_MENU_SCENE__

#include "cocos2d.h"
#include "Generator.h"

USING_NS_CC;

class MainMenuScene: public Layer
{
	Generator* _generator;
public:
	static Scene* createScene();
	virtual bool init();
	virtual void update(float);
	CREATE_FUNC(MainMenuScene);
	virtual ~MainMenuScene(){ CC_SAFE_DELETE(_generator); };
	void play(Ref*);
};

#endif //__MAIN_MENU_SCENE__

