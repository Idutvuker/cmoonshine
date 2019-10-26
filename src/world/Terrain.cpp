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
	
	
	
	uint id = grid.rawId(x, y, z);
	grid[id] += val;
	
	glBindBuffer(GL_TEXTURE_BUFFER, tbo);
	glBufferSubData(GL_TEXTURE_BUFFER, id * sizeof(float), sizeof(float), grid.data + id);
	
	ivec3 from = ivec3(x - 1, y - 1, z - 1);
	ivec3 to = ivec3(x + 1, y + 1, z + 1);
	grid.clamp(from);
	grid.clamp(to);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	deleteFromBuffer(from, to);
	
	tmp_indices.clear();
	preMarchingCubes(grid, isolevel, tmp_indices, from, to);
	addToBuffer(tmp_indices);
}

void Terrain::deleteFromBuffer(const ivec3 &from, const ivec3 &to)
{
	int k = 0;
	for (int x = from.x; x < to.x; x++)
		for (int y = from.y; y < to.y; y++)
			for (int z = from.z; z < to.z; z++)
			{
				int curId = grid.rawId(x, y, z);
				int loc = locTable[curId];
				
				if (loc != -1)
				{
					int last = voxelNum - 1;
					
					locTable[indices[last]] = loc;
					indices[loc] = indices[last];
					
					locTable[curId] = -1;
					
					glBufferSubData(GL_ARRAY_BUFFER, loc * sizeof(GLint), sizeof(GLint), indices + last);
					
					voxelNum--;
					k++;
				}
			}
	
	//glBufferSubData(GL_TEXTURE_BUFFER, id * sizeof(float), sizeof(float), grid.data + id);
	//voxelNum -= num;
	//if (voxelNum < 0)
	//	Log::e("Voxel num less then zero");
}

void Terrain::addToBuffer(const std::vector<int> &vec)
{
	for (int i = 0; i < (int) vec.size(); i++)
	{
		locTable[vec[i]] = voxelNum + i;
		indices[voxelNum + i] = vec[i];
	}
	
	glBufferSubData(GL_ARRAY_BUFFER, voxelNum * sizeof(GLint), vec.size() * sizeof(GLint), vec.data());
	
	voxelNum += (int) vec.size();
}

void Terrain::draw(const RenderContext &context)
{
	material->prepare(context);
	
	glBindVertexArray(vao);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_BUFFER, buf_tex);
	
//	glActiveTexture(GL_TEXTURE1);
//	glBindTexture(GL_TEXTURE_BUFFER, mc_tex);
	
	glDrawArrays(GL_POINTS, 0, voxelNum);
	glBindVertexArray(0);
}

Terrain::Terrain() {
	BaseMaterial::Definition def;
	def.vertexShaderFilepath = "res/shaders/terrain.vert";
	def.fragmentShaderFilepath = "res/shaders/terrain.frag";
	def.geometryShaderFilepath = "res/shaders/terrain.geom";
	def.defines = {
			"DIMX " + std::to_string(dimX),
			"DIMY " + std::to_string(dimY),
			"DIMZ " + std::to_string(dimZ),
			"ISOLEVEL " + std::to_string(isolevel)};
	
	material = new BaseMaterial(def);
	
	
	for (int i = 0; i < dimX * dimY * dimZ; i++)
	{
		locTable[i] = -1;
		indices[i] = -1;
	}
	
	//transform = translate(IDENTITY_MATRIX, vec3(-5, -5, -5));
	
	grid(1, 1, 1) = -1.f;
//	grid(1, 1, 2) = -2.f;
//
//	grid(1, 2, 1) = -4.f;
//	grid(1, 3, 1) = -4.f;
//	grid(1, 2, 2) = -3.f;
//	grid(2, 2, 2) = -3.f;
//	grid(2, 3, 2) = -3.f;
//	grid(2, 4, 2) = -3.f;
//	grid(2, 5, 2) = -3.f;
//	grid(2, 6, 2) = -3.f;
//	grid(2, 7, 2) = -3.f;
	
	//ivec3(chunkSize));//
	
	

	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, dimX * dimY * dimZ * sizeof(GLint), nullptr, GL_STREAM_DRAW);
	
	glVertexAttribIPointer(0, 1, GL_INT, 4, MACRO_BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);
	
	
	
	//Data buffer
	glGenBuffers(1, &tbo);
	glBindBuffer(GL_TEXTURE_BUFFER, tbo);
	glBufferData(GL_TEXTURE_BUFFER, dimX * dimY * dimZ * sizeof(float), grid.data, GL_STREAM_DRAW);
	
	glGenTextures(1, &buf_tex);
	glBindTexture(GL_TEXTURE_BUFFER, buf_tex);
	glTexBuffer(GL_TEXTURE_BUFFER, GL_R32F, tbo);
	material->setShaderUniform("data", 0);
	
	glBindVertexArray(0);
	
	tmp_indices.clear();
	preMarchingCubes(grid, isolevel, tmp_indices, ivec3(0, 0, 0), ivec3(dimX - 1, dimY - 1, dimZ - 1));
	addToBuffer(tmp_indices);
	
}

Terrain::~Terrain()
{
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &tbo);
	glDeleteTextures(1, &buf_tex);
	glDeleteTextures(1, &mc_tex);
}


