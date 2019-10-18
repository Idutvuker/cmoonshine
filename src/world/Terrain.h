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
	
	static const int dimX = 16;
	static const int dimY = 16;
	static const int dimZ = 16;
	
	PackedVoxVertex vertices[3 * dimX * dimY * dimZ];
	
	Buffer3<float, dimX, dimY, dimZ> grid{};
	
	GLuint vao;
	GLuint vbo;
	GLuint tbo;
	GLuint buf_tex, mc_tex;
	
	int voxelCount;
	
	
	BaseMaterial material{
						"res/shaders/terrain.vert",
						"res/shaders/terrain.frag", {},
						"#define DIMX " + std::to_string(dimX) +
						"\n#define DIMY " + std::to_string(dimY) +
	  					"\n#define DIMZ " + std::to_string(dimZ)+"\n",
	  					"res/shaders/terrain.geom"
	};
	
public:
	const float isolevel = -1.f;
	
	
	
	void change(vec3 pos, float val);
	
	
	virtual void draw(const RenderContext &context) override;
	Terrain();
	
	virtual ~Terrain() override;
};


