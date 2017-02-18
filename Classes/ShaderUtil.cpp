#include "ShaderUtil.h"

GLProgram* ShaderUtil::loadShader(const std::string& path)
{
	auto glCache = GLProgramCache::getInstance();
	GLProgram* prog = glCache->getGLProgram(path);
	if (!prog)
	{
		auto fs = FileUtils::getInstance();

		auto fragPath = fs->fullPathForFilename(path + ".fsh");
		auto vertPath = fs->fullPathForFilename(path + ".vsh");

		std::string fragmentSource = fs->getStringFromFile(fragPath);
		std::string vertexSource = fs->getStringFromFile(vertPath);

		auto fragB = fragmentSource.c_str();
		auto vertB = vertexSource.c_str();

		prog = GLProgram::createWithByteArrays(vertB, fragB);

		glCache->addGLProgram(prog, path);
	}

	return prog;
}

GLProgram* ShaderUtil::loadShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	auto glCache = GLProgramCache::getInstance();
	GLProgram* prog = glCache->getGLProgram(vertexShader + fragmentShader);
	if (!prog)
	{
		auto fs = FileUtils::getInstance();

		auto fragPath = fs->fullPathForFilename(vertexShader + ".fsh");
		auto vertPath = fs->fullPathForFilename(fragmentShader + ".vsh");

		std::string fragmentSource = fs->getStringFromFile(fragPath);
		std::string vertexSource = fs->getStringFromFile(vertPath);

		auto fragB = fragmentSource.c_str();
		auto vertB = vertexSource.c_str();

		prog = GLProgram::createWithByteArrays(vertB, fragB);

		glCache->addGLProgram(prog, vertexShader + fragmentShader);
	}

	return prog;
}