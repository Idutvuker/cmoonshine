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
	
	
	const int r = 2;
	
	ivec3 from = ivec3(x - r, y - r, z - r);
	ivec3 to = ivec3(x + r, y + r, z + r);
	
	grid.clamp(from);
	grid.clamp(to);
	
	for (int ex = from.x; ex < to.x; ex++)
		for (int ey = from.y; ey < to.y; ey++)
			for (int ez = from.z; ez < to.z; ez++)
			{
				//vec3 dr = vec3(ex, ey, ez);
				float dx = (ex - pos.x);
				float dy = (ey - pos.y);
				float dz = (ez - pos.z);
				float len = sqrtf(dx*dx + dy*dy + dz*dz);
				
				uint id = grid.rawId(ex, ey, ez);
				//if (grid[id] > -4.f)
				grid[id] += max(0.7f + r - len, 0.f) * val;
			}
	
	
	
	from = ivec3(x - r - 2, y - r - 2, z - r - 2);
	to = ivec3(x + r + 2, y + r + 2, z + r + 2);
	
	grid.clamp(from);
	grid.clamp(to);
	
	glBindBuffer(GL_TEXTURE_BUFFER, tbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	tmp_indices.clear();
	MarchingCubes::preMarchingCubes(grid, isolevel, tmp_indices, from, to);
	
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	deleteFromBuffer(from, to);
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
					int last = numIndices - 1;
					
					locTable[indices[last]] = loc;
					indices[loc] = indices[last];
					
					locTable[curId] = -1;
					
					//Copy last element to the deleted element location
					glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, loc * sizeof(GLuint), sizeof(GLuint), indices + last);
					
					numIndices--;
					k++;
				}
			}
}

void Terrain::addToBuffer(const std::vector<uint32> &vec)
{
	for (int i = 0; i < (int) vec.size(); i++)
	{
		locTable[vec[i]] = numIndices + i;
		indices[numIndices + i] = vec[i];
	}
	
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(GLuint), vec.size() * sizeof(GLuint), vec.data());
	
	numIndices += (int) vec.size();
}

void Terrain::draw(const RenderContext &context)
{
	material->prepare(context);
	
	glBindVertexArray(vao);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_BUFFER, buf_tex);
	
	//for (int i = 0; i < numIndices; i++)
	//	Log::d(indices[i]);
//	glActiveTexture(GL_TEXTURE1);
//	glBindTexture(GL_TEXTURE_BUFFER, mc_tex);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	//glDrawArrays(GL_POINTS, 0, numIndices);
	//glDrawArrays(GL_POINTS, 0, dimX * dimY * dimZ);
	glDrawElements(GL_POINTS, numIndices, GL_UNSIGNED_INT, nullptr);
	
	glBindVertexArray(0);
}

Terrain::Terrain() {
	BaseMaterial::Definition def;
	def.vertexShaderFilepath = "res/shaders/terrain.vert";
	def.fragmentShaderFilepath = "res/shaders/terrain.frag";
	def.geometryShaderFilepath = "res/shaders/terrain.geom";
	glPointSize(10);
	def.defines = {
			"DIMX " + std::to_string(dimX),
			"DIMY " + std::to_string(dimY),
			"DIMZ " + std::to_string(dimZ),
			"ISOLEVEL " + std::to_string(isolevel)};
	
	material = new BaseMaterial(def);
	
	
	for (int i = 0; i < dimX * dimY * dimZ; i++)
	{
		locTable[i] = -1;
		indices[i] = 0;
	}
	
	//transform = translate(IDENTITY_MATRIX, vec3(-5, -5, -5));
	
	grid(1, 1, 1) = -1.f;
//	grid(1, 1, 2) = -2.f;
//
//	grid(2, 2, 2) = -1.f;
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
	glGenBuffers(1, &ebo);
	glGenVertexArrays(1, &vao);
	
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, dimX * dimY * dimZ * sizeof(GLint), nullptr, GL_STREAM_DRAW);
	
	
	glVertexAttribIPointer(0, 1, GL_INT, 4, MACRO_BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);
	
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, dimX * dimY * dimZ * sizeof(GLuint), indices, GL_STREAM_DRAW);
	
	
	//Data buffer
	glGenBuffers(1, &tbo);
	glBindBuffer(GL_TEXTURE_BUFFER, tbo);
	glBufferData(GL_TEXTURE_BUFFER, 3 * dimX * dimY * dimZ * sizeof(GLuint), nullptr, GL_STREAM_DRAW);
	
	glGenTextures(1, &buf_tex);
	glBindTexture(GL_TEXTURE_BUFFER, buf_tex);
	glTexBuffer(GL_TEXTURE_BUFFER, GL_R32UI, tbo);
	material->setShaderUniform("data", 0);
	
	glBindVertexArray(0);
	
	
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_TEXTURE_BUFFER, tbo);
	tmp_indices.clear();
	
	MarchingCubes::preMarchingCubes(grid, isolevel, tmp_indices, ivec3(0, 0, 0), ivec3(dimX - 1, dimY - 1, dimZ - 1));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	addToBuffer(tmp_indices);
}

Terrain::~Terrain()
{
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	glDeleteBuffers(1, &tbo);
	glDeleteTextures(1, &buf_tex);
}


