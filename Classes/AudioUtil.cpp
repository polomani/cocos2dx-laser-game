#include <SimpleAudioEngine.h>
#include "AudioUtil.h"
#include "cocos2d.h"

using namespace CocosDenshion;


// check for more information
// http://www.cocos2d-x.org/wiki/Audio
// audio converter - http://audio.online-convert.com/ru/convert-to-ogg
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define JUMP_EFFECT "audio/jump_effect.wav"
#define LASER_HIT_EFFECT "audio/laser_hit.wav"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define JUMP_EFFECT "audio/jump_effect.ogg"
#define LASER_HIT_EFFECT "audio/laser_hit.ogg"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define GAME_OVER "audio/game_over.mp3"
#define LASER_MOVE_BACKGROUND "audio/laser_move_background.mp3"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#define GAME_OVER "audio/game_over.wav"
#define LASER_MOVE_BACKGROUND "audio/laser_move_background.wav"
#endif


bool AudioUtil::_init = false;
bool AudioUtil::_mute = false;


void AudioUtil::init()
{
	if (!_init)
	{
		SimpleAudioEngine* engine = SimpleAudioEngine::getInstance();
		engine->preloadEffect(JUMP_EFFECT);
		engine->preloadEffect(LASER_HIT_EFFECT);
		engine->preloadBackgroundMusic(GAME_OVER);
		engine->preloadBackgroundMusic(LASER_MOVE_BACKGROUND);
		_init = true;
	}
}

void AudioUtil::jumpEffect()
{
	init();
	if (!_mute)
	{
		SimpleAudioEngine::getInstance()->playEffect(JUMP_EFFECT);
	}
}

void AudioUtil::laserHitEffect()
{
	init();
	if (!_mute)
	{
		SimpleAudioEngine::getInstance()->playEffect(LASER_HIT_EFFECT);
	}
}

void AudioUtil::gameOverPlayground()
{
	init();
	if (!_mute)
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic(GAME_OVER);
	}
}

void AudioUtil::pauseBackgroundMusic()
{
	SimpleAudioEngine* engine = SimpleAudioEngine::getInstance();
	engine->pauseBackgroundMusic();
}

void AudioUtil::resumeBackgroundMusic()
{
	SimpleAudioEngine* engine = SimpleAudioEngine::getInstance();
	engine->resumeBackgroundMusic();
	if (_mute)
	{
		mute();
	}
}

void AudioUtil::startLazerMoveBackground()
{
	init();
	SimpleAudioEngine* engine = SimpleAudioEngine::getInstance();
	engine->playBackgroundMusic(LASER_MOVE_BACKGROUND, true);
	if (_mute)
	{
		mute();
	}
}

void AudioUtil::endLazerMoveBackground()
{
	SimpleAudioEngine* engine = SimpleAudioEngine::getInstance();
	engine->stopBackgroundMusic();
}

void AudioUtil::mute()
{
	_mute = true;
	SimpleAudioEngine* engine = SimpleAudioEngine::sharedEngine();
	engine->pauseAllEffects();
	engine->pauseBackgroundMusic();
}

void AudioUtil::unmute()
{
	_mute = false;
	SimpleAudioEngine* engine = SimpleAudioEngine::sharedEngine();
	engine->resumeAllEffects();
	engine->resumeBackgroundMusic();
}