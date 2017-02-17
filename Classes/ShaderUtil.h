#ifndef _SHADER_UTIL_
#define _SHADER_UTIL_

#include "cocos2d.h"
#include <string.h>

using namespace cocos2d;

class ShaderUtil
{
private:
	ShaderUtil() { };
	~ShaderUtil() { };
	ShaderUtil& operator=(const ShaderUtil&) { return *this; }
	ShaderUtil(const ShaderUtil&) { }
public:
	static GLProgram* loadShader(const std::string&);
	static GLProgram* loadShader(const std::string& vertexShader, const std::string& fragmentShader);
};

#endif