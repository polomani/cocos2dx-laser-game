#ifndef _GAME_OVER_MENU_H_
#define _GAME_OVER_MENU_H_
#include "cocos2d.h"

class HelloWorld;
class GameOverMenu : public cocos2d::LayerColor
{
private:
	HelloWorld* _gameScene;
public:
	CREATE_FUNC(GameOverMenu);

	GameOverMenu();

	virtual bool init();

	void show();

	void setGameScene(HelloWorld* h) { _gameScene = h; };

	void menuRestartClick(cocos2d::Ref* pSender);
};

#endif

