#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Generator.h"
#include "GameGUIFacade.h"
#include "Hero.h"
#include "GameOverMenu.h"

USING_NS_CC;

class GameScene : public Layer
{
private:
	static Scene* _scene;

	float _score;

	GameGUIFacade* _gui;

	Generator* _generator;

	Hero* _hero;

	bool _running = true;

	CREATE_FUNC(GameScene);
public:

	static GameScene* getInstance();

	static Scene* getSceneInstance();

    virtual bool init();

	virtual void update(float);

	void setScore(float);

	void onMouseDown(Event *event);
	virtual bool onTouchBegan(Touch*, Event*);
	virtual void onEnterTransitionDidFinish();
    
    // a selector callback
    void menuCloseCallback(Ref* pSender);
    
	GameGUIFacade* getGui() { return _gui; };
	bool isRunning();
	void setRunning(bool b);
	static void reverse(Vec2&);
};

#endif // __GAME_SCENE_H__
