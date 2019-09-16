#include "VertexDataType.h"

VertexDataType::VertexDataType(VertexDataType::EType type) : type(type) {}

int VertexDataType::getSize() const {
	switch (type)
	{
		case VertexDataType::POSITION:
			return 3;
		case VertexDataType::NORMAL:
			return 3;
		case VertexDataType::TEXCOORD:
			return 2;
	}
}

GLenum VertexDataType::getGLType() const {
	switch (type)
	{
		case VertexDataType::POSITION:
			return GL_FLOAT;
		case VertexDataType::NORMAL:
			return GL_FLOAT;
		case VertexDataType::TEXCOORD:
			return GL_FLOAT;
	}
}

GLenum VertexDataType::getGLTypeSize() const {
	switch (getGLType())
	{
		case GL_FLOAT:
			return sizeof(GLfloat);
		case GL_INT:
			return sizeof(GLint);
		case GL_BOOL:
			return sizeof(GLboolean);
		case GL_HALF_FLOAT:
			return sizeof(GLhalf);
	}
}
