#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../util/Logger.h"

class Shader
{
public:
	GLuint shader;

	Shader(GLenum type, const char* source);

	void attach(GLuint program);

	void deleteShader();
};