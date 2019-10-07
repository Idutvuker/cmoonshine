#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../util/Logger.h"

class Shader
{
public:
	GLuint shader;

	static Shader loadFromFile(GLenum type, const std::string &filepath, const std::string &header);

	Shader(GLenum type, const char* source);

	void attach(GLuint program);

	void deleteShader();
};