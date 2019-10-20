#include <GL/glew.h>
#include "VertexAttrib.h"
#include "../util/Logger.h"


GLsizei VertexAttrib::getByteSize() const
{
	int type_size = -1;
	switch (type)
	{
		case GL_FLOAT:
			type_size = sizeof(GLfloat);
			break;
		case GL_INT:
			type_size = sizeof(GLint);
			break;
		case GL_BOOL:
			type_size = sizeof(GLboolean);
			break;
		case GL_HALF_FLOAT:
			type_size = sizeof(GLhalf);
			break;
		default:
			type_size = -1;
			Log::e("Unsupported type in vertex attribute. Index, type: ", index, type);
	}
	
	return size * type_size;
}
