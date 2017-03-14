#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Generator.h"
#include "GameGUIFacade.h"
#include "Hero.h"
#include "GameOverMenu.h"

class GameScene : public cocos2d::Layer
{
private:
	/*
	for some devices position should be reverse by axis Oy
	*/
	static void reverse(cocos2d::Vec2&);
	float _score;

	GameGUIFacade* _gui;

	Generator* _generator;

	Hero* _hero;

	bool _running = true;
public:

    static cocos2d::Scene* createScene();

    virtual bool init();

	virtual void update(float);

	void setScore(float);

	void onMouseDown(cocos2d::Event *event);
	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	virtual void onEnterTransitionDidFinish();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
	CREATE_FUNC(GameScene);

	bool isRunning();
	void setRunning(bool b);
};

#endif // __GAME_SCENE_H__
