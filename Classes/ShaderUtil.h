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
	static GLProgram* loadShader(const std::string& name, const std::string& path);
	static GLProgram* loadShader(const std::string& name, const std::string& pathVertex, const std::string& pathFragment);
	static GLProgram* loadShaderFromStrings(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
};

#endif