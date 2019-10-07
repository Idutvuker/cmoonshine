#include "Terrain.h"
#include "../materials/MaterialManager.h"
#include "../voxel/MarchingCubes.h"

#define MACRO_BUFFER_OFFSET(idx) (static_cast<char*>(0) + (idx))

void Terrain::draw(const RenderContext &context)
{
	material.prepare(context);
	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indCount, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}

Terrain::Terrain()
{
	transform = translate(IDENTITY_MATRIX, vec3(-5, -5, -5));
	
//	data(1, 1, 1) = -4.f;
//	data(1, 1, 2) = -2.f;

	data(1, 2, 1) = -4.f;
	data(1, 3, 1) = -4.f;
	data(1, 2, 2) = -3.f;
	data(2, 2, 2) = -3.f;

//	for (int x = 0; x < dimX; x++)
//		for (int y = 0; y < dimY; y++)
//			for (int z = 0; z < dimZ; z++)
//			{
//				int rx = x - 5;
//				int ry = y - 5;
//				int rz = z - 5;
//				data(x, y, z) = rx*rx + ry*ry + rz*rz;
//			}
	
	
	
	
	indCount = marchingCubes(data, -1.f, vertices, indices);
	Log::d(indCount);
	
	Log::d("size:", sizeof(vertices));
	Log::d("size index:", sizeof(indices));
	
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &ibo);
	glGenBuffers(1, &vbo);
	
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STREAM_DRAW);
	
	glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, 4, MACRO_BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);
	
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
}

Terrain::~Terrain()
{
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}