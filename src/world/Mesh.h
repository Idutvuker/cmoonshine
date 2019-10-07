#pragma once

#include "../common/BaseMaterial.h"
#include "Drawable.h"
#include <memory>



class Mesh : public Drawable
{
	MACRO_NODE_DECL()
	


private:



protected:
	Mesh(bool indexed);
	
	void bufferData(const VertexAttribSetup &vas);
	
	const bool indexed;
	GLsizei elemCount;
	
	GLuint vao, vbo, ibo;
	
	std::vector<float> vertices;
	std::vector<int> indices;
	
public:
	
	std::shared_ptr<BaseMaterial> material;

	Mesh(const std::vector<float> &vertices, const std::vector<int> &indices, std::shared_ptr<BaseMaterial> material);
	Mesh(const std::vector<float> &vertices, std::shared_ptr<BaseMaterial> material);
	
	virtual ~Mesh() override;

	virtual void draw(const RenderContext &context) override;

};


