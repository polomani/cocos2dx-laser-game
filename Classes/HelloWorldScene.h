#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Generator.h"
#include "GameGUI.h"
#include "Hero.h"

class HelloWorld : public cocos2d::Layer
{
private:
	/*
	for some devices position should be reverse by axis Oy
	*/
	static void reverse(cocos2d::Vec2&);
	float _score;
public:
	GameGUI* _gui;

	Generator* _generator;

	Hero* _hero;

    static cocos2d::Scene* createScene();

    virtual bool init();

	virtual void update(float);

	void setScore(float);

	void onMouseDown(cocos2d::Event *event);
	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
