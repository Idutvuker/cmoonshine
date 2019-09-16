#include "GLDrawable.h"
#include "../util/Logger.h"

void GLDrawable::bufferData(const VertexAttribSetup &vas)
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	
	if (indexed)
		glGenBuffers(1, &ibo);
	
	glBindVertexArray(vao);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	
	
	if (indexed)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint) * indices.size(), indices.data(), GL_STATIC_DRAW);
		elemCount = indices.size();
	}
	else
	{
		elemCount = vertices.size() / vas.getVertexSize();
	}
	
	for (auto attr : vas.setup)
	{
		glVertexAttribPointer(attr.index, attr.size, attr.type, GL_FALSE, attr.stride,
							  (void *)(attr.offset));
		glEnableVertexAttribArray(attr.index);
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

GLDrawable::GLDrawable(const std::vector<float> &vertices, const std::vector<int> &indices,
					   const VertexAttribSetup &vas) :
		vertices(vertices),
		indices(indices),
		indexed(true)
{
	bufferData(vas);
}

GLDrawable::GLDrawable(const std::vector<float> &vertices, const VertexAttribSetup &vas):
	vertices(vertices),
	indexed(false)
{
	bufferData(vas);
}

GLDrawable::~GLDrawable()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void GLDrawable::draw()
{
	glBindVertexArray(vao);
	
	if (indexed)
		glDrawElements(GL_TRIANGLES, elemCount, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, elemCount);
	
	glBindVertexArray(0);
}


