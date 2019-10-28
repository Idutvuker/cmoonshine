#pragma once


#include <GL/glew.h>
#include "Drawable.h"
#include "../system/RenderContext.h"
#include "../voxel/VoxVertex.h"
#include "../voxel/Buffer3.h"
#include "../common/BaseMaterial.h"

class Terrain : public Drawable
{
	MACRO_NODE_DECL();
private:
	
	static const int dimX = 32;
	static const int dimY = 32;
	static const int dimZ = 32;
	
	//PackedVoxVertex vertices[3 * dimX * dimY * dimZ];
	
	// On VRAM and RAM
	uint32 indices[dimX * dimY * dimZ];
	int numIndices = 0;
	
	// On RAM
	//VoxVertex cache[dimX][dimY][dimZ][3];
	int locTable[dimX * dimY * dimZ];
	Buffer3<float, dimX, dimY, dimZ> grid{};
	
	std::vector<uint32> tmp_indices;
	
	
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	GLuint tbo;
	GLuint buf_tex;
	
	BaseMaterial *material;
	
	void addToBuffer(const std::vector<uint32> &vec);
	void deleteFromBuffer(const ivec3 &from, const ivec3 &to);
	
public:
	const float isolevel = -0.5f;
	
	
	
	void change(vec3 pos, float val);
	
	
	virtual void draw(const RenderContext &context) override;
	Terrain();
	
	virtual ~Terrain() override;
};


