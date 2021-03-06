#ifndef _STORAGE_H_
#define _STORAGE_H_

#include "Static.h"

class Storage
{
public:
	static int geti(const char*);
	static void seti(const char*, int i);

	static string gets(const char*);
	static void sets(const char*, string& s);

	static double getd(const char*);
	static void setd(const char*, double d);

	static bool getb(const char*);
	static void setb(const char*, bool b);
private:
	CC_DISALLOW_COPY_AND_ASSIGN(Storage)
};

#endif