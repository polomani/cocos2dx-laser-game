#include "cocos2d.h"
using namespace cocos2d;

#include "Storage.h"

UserDefault* Storage::_default = UserDefault::getInstance();

int Storage::geti(const char* key)
{
	return _default->getIntegerForKey(key);
}
void Storage::seti(const char* key, int value)
{
	_default->setIntegerForKey(key, value);
}

double Storage::getd(const char* key)
{
	return _default->getDoubleForKey(key);
}
void Storage::setd(const char* key, double value)
{
	_default->setDoubleForKey(key, value);
}

string Storage::gets(const char* key)
{
	return _default->getStringForKey(key);
}
void Storage::sets(const char* key, string& value)
{
	_default->setStringForKey(key, value);
}