#ifndef __GameGUI_h__
#define __GameGUI_h__
#include "cocos2d.h"

USING_NS_CC;

class GameGUI : public Layer
{
private:
	Label* _score;
public:	

	CREATE_FUNC(GameGUI);
	virtual bool init();

	void setScore(int);
};

#endif

