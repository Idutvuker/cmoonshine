#include "Terrain.h"
#include "../materials/MaterialManager.h"
#include "../voxel/MarchingCubes.h"

#define MACRO_BUFFER_OFFSET(idx) (static_cast<char*>(0) + (idx))

void Terrain::change(vec3 pos, float val)
{
	int x = (int)(pos.x + 0.5f);
	int y = (int)(pos.y + 0.5f);
	int z = (int)(pos.z + 0.5f);
	
	if (!grid.inBounds(x, y, z))
		return;
	
	if (z == 0)
		return;
	
	uint id = grid.rawId(x, y, z);
	grid[id] += val;
	
	glBindBuffer(GL_TEXTURE_BUFFER, tbo);
	glBufferSubData(GL_TEXTURE_BUFFER, id * sizeof(float), sizeof(float), grid.data + id);
}

void Terrain::draw(const RenderContext &context)
{
	material->prepare(context);
	
	glBindVertexArray(vao);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_BUFFER, buf_tex);
	
//	glActiveTexture(GL_TEXTURE1);
//	glBindTexture(GL_TEXTURE_BUFFER, mc_tex);
	
	glDrawArrays(GL_POINTS, 0, voxelCount);
	glBindVertexArray(0);
}

Terrain::Terrain()
{
	BaseMaterial::Definition def;
	def.vertexShaderFilepath = "res/shaders/terrain.vert";
	def.fragmentShaderFilepath = "res/shaders/terrain.frag";
	def.geometryShaderFilepath = "res/shaders/terrain.geom";
	def.header = "#define DIMX " + std::to_string(dimX) +
			"\n#define DIMY " + std::to_string(dimY) +
			"\n#define DIMZ " + std::to_string(dimZ)+"\n";
	
	material = new BaseMaterial(def);
	
	
	
	//transform = translate(IDENTITY_MATRIX, vec3(-5, -5, -5));
	
	grid(1, 1, 1) = -4.f;
	grid(1, 1, 2) = -2.f;

	grid(1, 2, 1) = -4.f;
	grid(1, 3, 1) = -4.f;
	grid(1, 2, 2) = -3.f;
//	grid(2, 2, 2) = -3.f;
//	grid(2, 3, 2) = -3.f;
//	grid(2, 4, 2) = -3.f;
//	grid(2, 5, 2) = -3.f;
//	grid(2, 6, 2) = -3.f;
//	grid(2, 7, 2) = -3.f;
	
	//ivec3(chunkSize));//
	//marchingCubes(grid, isolevel, vertices, this, ivec3(0, 0, 0), ivec3(dimX, dimY, dimZ));
	
	
	voxelCount = dimX * dimY * dimZ;
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	//Data buffer
	glGenBuffers(1, &tbo);
	glBindBuffer(GL_TEXTURE_BUFFER, tbo);
	glBufferData(GL_TEXTURE_BUFFER, voxelCount * sizeof(float), grid.data, GL_STREAM_DRAW);
	
	glGenTextures(1, &buf_tex);
	glBindTexture(GL_TEXTURE_BUFFER, buf_tex);
	glTexBuffer(GL_TEXTURE_BUFFER, GL_R32F, tbo);
	material->setShaderUniform("data", 0);
	
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Terrain::~Terrain()
{
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &tbo);
	glDeleteTextures(1, &buf_tex);
	glDeleteTextures(1, &mc_tex);
}


