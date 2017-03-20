#ifndef _AUDIO_H_
#define _AUDIO_H_

#include "cocos2d.h"
using namespace cocos2d;

class AudioUtil
{
public:
	static void jumpEffect();
	
	static void laserHitEffect();

	static void gameOverPlayground();

	static void pauseBackgroundMusic();
	static void resumeBackgroundMusic();

	static void startLazerMoveBackground();
	static void endLazerMoveBackground();

	static void mute();
	static void unmute();
private:
	static bool _init;
	static bool _mute;
	static void init();
	CC_DISALLOW_COPY_AND_ASSIGN(AudioUtil)
};

#endif