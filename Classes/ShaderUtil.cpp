#include "ShaderUtil.h"

#define FRAGMENT_EXTENSION ".frag"
#define VERTEX_EXTENSION ".vert"

GLProgram* ShaderUtil::loadShader(const std::string& name, const std::string& path)
{
	auto glCache = GLProgramCache::getInstance();
	GLProgram* prog = glCache->getGLProgram(name);
	if (!prog)
	{
		auto fs = FileUtils::getInstance();

		auto fragPath = fs->fullPathForFilename(path + FRAGMENT_EXTENSION);
		auto vertPath = fs->fullPathForFilename(path + VERTEX_EXTENSION);

		std::string fragmentSource = fs->getStringFromFile(fragPath);
		std::string vertexSource = fs->getStringFromFile(vertPath);

		auto fragB = fragmentSource.c_str();
		auto vertB = vertexSource.c_str();

		prog = GLProgram::createWithByteArrays(vertB, fragB);

		glCache->addGLProgram(prog, name);
	}

	return prog;
}

GLProgram* ShaderUtil::loadShader(const std::string& name, const std::string& vertexShader, const std::string& fragmentShader)
{
	auto glCache = GLProgramCache::getInstance();
	GLProgram* prog = glCache->getGLProgram(name);
	if (!prog)
	{
		auto fs = FileUtils::getInstance();

		auto fragPath = fs->fullPathForFilename(vertexShader + FRAGMENT_EXTENSION);
		auto vertPath = fs->fullPathForFilename(fragmentShader + VERTEX_EXTENSION);

		std::string fragmentSource = fs->getStringFromFile(fragPath);
		std::string vertexSource = fs->getStringFromFile(vertPath);

		auto fragB = fragmentSource.c_str();
		auto vertB = vertexSource.c_str();

		prog = GLProgram::createWithByteArrays(vertB, fragB);

		glCache->addGLProgram(prog, name);
	}

	return prog;
}

GLProgram* ShaderUtil::loadShaderFromStrings(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
{
	auto glCache = GLProgramCache::getInstance();
	GLProgram* prog = glCache->getGLProgram(name);
	if (!prog)
	{
		prog = GLProgram::createWithByteArrays(vertexSource.c_str(), fragmentSource.c_str());

		glCache->addGLProgram(prog, name);
	}

	return prog;
}