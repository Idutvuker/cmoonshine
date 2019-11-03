#pragma once

#include "../common/VertexAttrib.h"
#include "../common/BaseMaterial.h"
#include "Drawable.h"
#include <memory>

class Mesh : public Drawable
{
	MACRO_NODE_DECL()
	


private:



protected:
	Mesh(bool indexed);
	
	void bufferData(const std::vector<VertexAttrib> &attribs);
	
	const bool indexed;
	GLsizei elemCount;
	
	GLuint vao, vbo, ibo;
	
	std::vector<float> vertices;
	std::vector<int> indices;
	
public:
	
	BaseMaterial *material;

	Mesh(const std::vector<float> &vertices, const std::vector<int> &indices, BaseMaterial *material);
	Mesh(const std::vector<float> &vertices, BaseMaterial *material);
	
	virtual ~Mesh() override;

	virtual void draw(const RenderContext &context) override;

};


