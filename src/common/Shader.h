#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../util/Logger.h"
#include "VertexAttrib.h"

class Shader
{
public:
	GLuint shader;

	Shader(GLenum type, const std::string &src);
	
	static std::string preprocess(const std::string &src);
	static std::string preprocessLayout(const std::string &src, std::vector<VertexAttrib> &attribs);
	
	void attach(GLuint program);

	void deleteShader();
};