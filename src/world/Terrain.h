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
	
	static const int dimX = 8;
	static const int dimY = 8;
	static const int dimZ = 8;
	
	//PackedVoxVertex vertices[3 * dimX * dimY * dimZ];
	
	Buffer3<float, dimX, dimY, dimZ> grid{};
	int locTable[dimX * dimY * dimZ];
	
	std::vector<int> tmp_indices;
	int voxelNum = 0;
	
	GLuint vao;
	GLuint vbo;
	GLuint tbo;
	GLuint buf_tex, mc_tex;
	
	BaseMaterial *material;
	
	void addToBuffer(const std::vector<int> &vec);
	void deleteFromBuffer(const ivec3 &from, const ivec3 &to);
	
public:
	const float isolevel = -1.f;
	int indices[dimX * dimY * dimZ];
	
	
	void change(vec3 pos, float val);
	
	
	virtual void draw(const RenderContext &context) override;
	Terrain();
	
	virtual ~Terrain() override;
};


