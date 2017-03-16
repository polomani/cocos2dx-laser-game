#ifndef _STORAGE_H_
#define _STORAGE_H_

#include "cocos2d.h"
using namespace cocos2d;

#include <string.h>
using namespace std;

class Storage
{
public:
	static int geti(const char*);
	static void seti(const char*, int i);

	static string gets(const char*);
	static void sets(const char*, string& s);

	static double getd(const char*);
	static void setd(const char*, double d);
private:
	static UserDefault* _default;

	CC_DISALLOW_COPY_AND_ASSIGN(Storage)
};

#endif