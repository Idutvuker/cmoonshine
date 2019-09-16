#include "Mesh.h"

#include <utility>

void Mesh::bufferData(const VertexAttribSetup &vas)
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
							  MACRO_BUFFER_OFFSET(attr.offset));
		glEnableVertexAttribArray(attr.index);
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Mesh::Mesh(const std::vector<float> &vertices, const std::vector<int> &indices, std::shared_ptr<BaseMaterial> material) :
		vertices(vertices),
		indices(indices),
		indexed(true),
		material(material)
{
	bufferData(material->vertexAttribSetup);
}

Mesh::Mesh(const std::vector<float> &vertices, std::shared_ptr<BaseMaterial> material) :
		vertices(vertices),
		indexed(false),
		material(material)
{
	bufferData(material->vertexAttribSetup);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void Mesh::draw(const RenderContext &context)
{
	material->prepare(context);
	
	glBindVertexArray(vao);
	
	if (indexed)
		glDrawElements(GL_TRIANGLES, elemCount, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, elemCount);
	
	glBindVertexArray(0);
}
