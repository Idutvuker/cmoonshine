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
	static const int chX = 1;
	static const int chY = 1;
	static const int chZ = 1;
	
	static const int chunkSize = 8;
	
	static const int dimX = chX * chunkSize;
	static const int dimY = chY * chunkSize;
	static const int dimZ = chZ * chunkSize;
	
	PackedVoxVertex vertices[3 * dimX * dimY * dimZ];
	std::vector<GLuint> indices[chX * chY * chZ];//[dimX * dimY * dimZ * 5];
	
	Buffer3<float, dimX, dimY, dimZ> data{};
	
	GLuint vao;
	GLuint vbo;
	GLuint ibos[chX * chY * chZ];
	
	
	BaseMaterial material{
						"res/shaders/terrain.vert",
						"res/shaders/terrain.frag", {},
						"#define DIMX " + std::to_string(dimX) +
						"\n#define DIMY " + std::to_string(dimY) +
	  					"\n#define DIMZ " + std::to_string(dimZ)
	};
	
public:
	const float isolevel = -1.f;
	
	static inline int getChunkId(int cx, int cy, int cz);
	inline std::vector<GLuint>* getChunkFromCoord(int x, int y, int z);
	
	void change(vec3 pos, float val);
	
	
	virtual void draw(const RenderContext &context) override;
	Terrain();
	
	virtual ~Terrain() override;
};


