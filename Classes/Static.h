#ifndef __STATIC__

#include "cocos2d.h"

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

#define COCOS2D_DEBUG 1

using namespace std;
using namespace cocos2d;

#endif //__STATIC__