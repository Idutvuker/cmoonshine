#pragma once

#include "Spatial.h"
#include "../common/GLDrawable.h"
#include "../common/BaseMaterial.h"
#include "../system/RenderContext.h"
#include <memory>

#define MACRO_BUFFER_OFFSET(idx) (static_cast<char*>(0) + (idx))

class Mesh : public Spatial
{
	MACRO_NODE_DECL()
	
private:
	void bufferData(const VertexAttribSetup &vas);

	const bool indexed;
	GLsizei elemCount;


protected:
	
	GLuint vao, vbo, ibo;
	
	std::vector<float> vertices;
	std::vector<int> indices;
	
public:
	//using GLDrawable::GLDrawable;
	
	std::shared_ptr<BaseMaterial> material;

	Mesh(const std::vector<float> &vertices, const std::vector<int> &indices, std::shared_ptr<BaseMaterial> material);
	Mesh(const std::vector<float> &vertices, std::shared_ptr<BaseMaterial> material);
	
	virtual ~Mesh() override;


	void draw(const RenderContext &context);

};


