#include "Terrain.h"
#include "../materials/MaterialManager.h"
#include "../voxel/MarchingCubes.h"

#define MACRO_BUFFER_OFFSET(idx) (static_cast<char*>(0) + (idx))

void Terrain::change(vec3 pos, float val) {
	int x = pos.x + 0.5f;
	int y = pos.y + 0.5f;
	int z = pos.z + 0.5f;
	
	if (!data.inBounds(x, y, z))
		return;
	
	if (z == 0)
		return;
	
	data(x, y, z) += val;
	
	int cx = x / chunkSize;
	int cy = y / chunkSize;
	int cz = z / chunkSize;
	
	ivec3 bv = vec3(cx * chunkSize, cy * chunkSize, cz * chunkSize);
	
	int ex = (cx == chX - 1) ? bv.x + 8 : bv.x + 9;
	int ey = (cy == chY - 1) ? bv.y + 8 : bv.y + 9;
	int ez = (cz == chZ - 1) ? bv.z + 8 : bv.z + 9;
	
	
	
	Log::d(x, y, z, to_string(bv));
	
	int id = getChunkId(cx, cy, cz);
	indices[id].resize(0);
	marchingCubes(data, isolevel, vertices, this, bv, ivec3(ex, ey, ez));
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibos[id]);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices[id].size() * sizeof(GLuint), indices[id].data());

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//for (int i = 0; i < 1536; i++)
	//	vertices[i] = 0;
	
//	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	for (int dx = max(x - 1, 0); dx < x + 1; dx++)
		for (int dy = max(y - 1, 0); dy < y + 1; dy++)
		{
			uint32 index = 3 * data.rawId(dx, dy, z - 1);
			//Log::d(dx, dy, z - 1);
			Log::d(vertices[index] >> 24);
			glBufferSubData(GL_ARRAY_BUFFER, index, 3 * 3 * sizeof(PackedVoxVertex), vertices + index);
		}
	//Log::d(indices[getChunkId(cx, cy, cz)].size());
}


int Terrain::getChunkId(int cx, int cy, int cz)
{
	return cx * chY * chZ + cy * chZ + cz;
}

std::vector<GLuint>* Terrain::getChunkFromCoord(int x, int y, int z)
{
	int cx = x / chunkSize;
	int cy = y / chunkSize;
	int cz = z / chunkSize;
	
	
	
	return indices + getChunkId(cx, cy, cz);
}

void Terrain::draw(const RenderContext &context)
{
	material.prepare(context);
	
	glBindVertexArray(vao);
	
	for (int i = 0; i < chX * chY * chZ; i++)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibos[i]);

		glDrawElements(GL_TRIANGLES, indices[i].size(), GL_UNSIGNED_INT, nullptr);
	}
	glBindVertexArray(0);
}

Terrain::Terrain()
{
	//transform = translate(IDENTITY_MATRIX, vec3(-5, -5, -5));
	
	data(1, 1, 1) = -4.f;
	data(1, 1, 2) = -2.f;

	data(1, 2, 1) = -4.f;
	data(1, 3, 1) = -4.f;
	data(1, 2, 2) = -3.f;
	data(2, 2, 2) = -3.f;
	data(2, 3, 2) = -3.f;
	data(2, 4, 2) = -3.f;
	data(2, 5, 2) = -3.f;
	data(2, 6, 2) = -3.f;
	data(2, 7, 2) = -3.f;
//	data(2, 8, 2) = -3.f;
//	data(2, 9, 2) = -3.f;
//	data(2, 10, 2) = -3.f;

//	for (int x = 0; x < dimX; x++)
//		for (int y = 0; y < dimY; y++)
//			for (int z = 0; z < dimZ; z++)
//			{
//				int rx = x - 5;
//				int ry = y - 5;
//				int rz = z - 5;
//				data(x, y, z) = rx*rx + ry*ry + rz*rz;
//			}

	
	//ivec3(chunkSize));//
	marchingCubes(data, isolevel, vertices, this, ivec3(0, 0, 0), ivec3(dimX, dimY, dimZ));
	
	Log::d("size:", sizeof(vertices));
	
	glGenBuffers(chX*chY*chZ, ibos);
	
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);
	
	for (int i = 0; i < chX * chY * chZ; i++)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibos[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices[i].capacity() * sizeof(GLuint), indices[i].data(), GL_STREAM_DRAW);
	}
	
	glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, 4, MACRO_BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);
	
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
}

Terrain::~Terrain()
{
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(chX * chY * chZ, ibos);
}


