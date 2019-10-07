#pragma once


#include <GL/glew.h>
#include "Drawable.h"
#include "../system/RenderContext.h"
#include "../voxel/VoxVertex.h"
#include "../voxel/VoxelGrid.h"
#include "../common/BaseMaterial.h"

class Terrain : public Drawable
{
	MACRO_NODE_DECL();
private:
//	static const int chX = 3;
//	static const int chY = 3;
//	static const int chZ = 3;
//	static const int chunkSize = 8;
//	VoxelGrid<float, chX * chunkSize, chY * chunkSize, chZ * chunkSize> data;
	
	static const int dimX = 10;
	static const int dimY = 10;
	static const int dimZ = 10;
	
	PackedVoxVertex vertices[3 * dimX * dimY * dimZ];
	GLuint indices[dimX * dimY * dimZ * 5];
	uint32 indCount;
	
	
	VoxelGrid<float, dimX, dimY, dimZ> data{};
	
	GLuint vao;
	GLuint vbo;
	GLuint ibo;
	
	BaseMaterial material{
						"res/shaders/terrain.vert",
						"res/shaders/terrain.frag", {},
						"#define DIMX " + std::to_string(dimX) +
						"\n#define DIMY " + std::to_string(dimY) +
	  					"\n#define DIMZ " + std::to_string(dimZ)
	};
	
public:
	virtual void draw(const RenderContext &context) override;
	Terrain();
	
	virtual ~Terrain() override;
};


