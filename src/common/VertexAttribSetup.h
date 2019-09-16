#pragma once
#include <GL/glew.h>
#include <vector>

#include "VertexDataType.h"

class VertexAttribSetup
{
public:

	VertexAttribSetup() = delete;

	struct VertexAttrib
	{
		int index = 0;
		int size = 0;
		GLenum type = GL_FLOAT;
		int stride = 0;
		int offset = 0;
	};


	VertexAttribSetup(const std::vector<VertexDataType> &dataTypes, bool batched = false);

	std::vector<VertexAttrib> setup;
	bool batched = false;
	
	int getVertexSize() const;
	
	
};