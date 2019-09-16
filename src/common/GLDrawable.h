#pragma once

#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <vector>

#include "VertexAttribSetup.h"



class GLDrawable
{
private:
	const bool indexed;
	GLsizei elemCount;
	
	void bufferData(const VertexAttribSetup &vas);
	
	
protected:

	GLuint vao, vbo, ibo;

	std::vector<float> vertices;
	std::vector<int> indices;

public:

	GLDrawable(const std::vector<float> &vertices, const std::vector<int> &indices, const VertexAttribSetup &vas);
	GLDrawable(const std::vector<float> &vertices, const VertexAttribSetup &vas);

	~GLDrawable();

	void draw();
	
	
};