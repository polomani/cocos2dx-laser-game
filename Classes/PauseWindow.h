#ifndef __PAUSE_WINDOW__
#define __PAUSE_WINDOW__

#include "cocos2d.h"
#include "GameGUIFacade.h"
USING_NS_CC;

class PauseWindow: public LayerColor  {
private:
	bool _paused;
public:
	CREATE_FUNC(PauseWindow);

	PauseWindow();
	virtual bool init();
	void pauseClickCallBack(Event* event);
	bool pauseTapCallBack(Touch* touch, Event* event);

	void show();
	void close();
	bool paused() { return _paused; };
	void paused(bool paused) { _paused = paused; };
};

#endif //__PAUSE_WINDOW__