#pragma once

#include <GL/glew.h>
#include <utility>
#include <string>

struct VertexDataType
{
	enum EType: int
	{
		POSITION,
		NORMAL,
		TEXCOORD
	};

	VertexDataType(EType type);

	int getSize() const;

	GLenum getGLType() const;

	GLenum getGLTypeSize() const;

private:
	EType type;
};