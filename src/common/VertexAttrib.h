#pragma once

#include "GL/glew.h"

struct VertexAttrib
{
	int index;
	int size;
	GLenum type;
	int stride;
	int offset;

//		VertexAttrib(int index, int size, GLenum type, int stride, int offset) :
//		index(index),
//		size(size),
//		type(type),
//		stride(stride),
//		offset(offset)
//		{}
	
	GLsizei getByteSize() const;
	
};