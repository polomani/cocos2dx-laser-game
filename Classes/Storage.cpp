#include "cocos2d.h"
using namespace cocos2d;

#include "Storage.h"

int Storage::geti(const char* key)
{
	return UserDefault::getInstance()->getIntegerForKey(key);
}
void Storage::seti(const char* key, int value)
{
	UserDefault::getInstance()->setIntegerForKey(key, value);
}

double Storage::getd(const char* key)
{
	return UserDefault::getInstance()->getDoubleForKey(key);
}
void Storage::setd(const char* key, double value)
{
	UserDefault::getInstance()->setDoubleForKey(key, value);
}

string Storage::gets(const char* key)
{
	return UserDefault::getInstance()->getStringForKey(key);
}
void Storage::sets(const char* key, string& value)
{
	UserDefault::getInstance()->setStringForKey(key, value);
}

bool Storage::getb(const char* key)
{
	return UserDefault::getInstance()->getBoolForKey(key);
}
void Storage::setb(const char* key, bool b)
{
	UserDefault::getInstance()->setBoolForKey(key, b);
}