#pragma once

#include "VoxVertex.h"
#include "Buffer3.h"
#include "MCTables.h"
#include "../util/geometry.h"


template <int sizeY, int sizeZ>
void packLayer(VoxVertex cache[sizeY][sizeZ][3], int xLayer, PackedVoxVertex vertices[])
{
	for (int y = 0; y < sizeY; y++)
		for (int z = 0; z < sizeZ; z++)
		{
			vertices[y * sizeY + z] = cache[y][z][].pack();
		}
}


template <typename T>
float interp(T val1, T val2, T isolevel)
{
	return (isolevel - val1)/((float)(val2 - val1));
}

template<typename T, int sizeX, int sizeY, int sizeZ>
uint32 marchingCubes(
		const Buffer3<T, sizeX, sizeY, sizeZ> &grid,
		T isolevel,
		PackedVoxVertex vertices[],
		Terrain * terrain,
		const ivec3 &from,
		const ivec3 &to)
{
	using namespace MCTABLES;
	
	VoxVertex cache[2][sizeY][sizeZ][3];
	
	uint32 indCount = 0;
	
	T values[8];
	
	struct VoxCoord{
		ivec3 pos;
		int dir;
	} voxCoord[12];
	
	for (int x = from.x; x < to.x; x++)
	{
		for (int y = from.y; y < to.y - 1; y++)
		{
			if (x == to.x - 1)
				break;
			for (int z = from.z; z < to.z - 1; z++)
			{
				
				int bits = 0;
				int power = 1;
				
				
				for (int i = 0; i < 8; i++) {
					ivec3 vox = ivec3(x, y, z) + VOXEL_POSITION[i];
					values[i] = grid(vox.x, vox.y, vox.z);
					
					if (values[i] < isolevel)
						bits |= power;
					
					power <<= 1;
				}
				
				int edges = EDGE_TABLE[bits];
				
				if (edges == 0)
					continue;
				
				power = 1;
				
				for (int i = 0; i < 12; i++) {
					if (edges & power) {
						int v1 = EDGE_ORDER[i * 2];
						int v2 = EDGE_ORDER[i * 2 + 1];
						
						ivec3 vox = ivec3(x, y, z) + VOXEL_POSITION[v1];
						uint32 index = 3 * grid.rawId(vox) + EDGE_DIR[i];
						
						
						if (!EDGE_CACHED[i] ||
							(x == 0 && (i == 3 || i == 8 || i == 7 || i == 11)) ||    // left cube face
							(y == 0 && (i == 0 || i == 1 || i == 2 || i == 3)) ||    // bottom cube face
							(z == 0 && (i == 0 || i == 9 || i == 4 || i == 8)))        // front cube face)
						{
							cache[vox.x % 2][vox.y][vox.z][EDGE_DIR[i]].edgePos = interp(values[v1], values[v2], isolevel);
						}
						
						voxCoord[i].pos = vox;
						voxCoord[i].dir = EDGE_DIR[i];
					}
					
					power <<= 1;
				}
				
				
				int i = 0;
				
				while (TRI_TABLE[bits][i] != -1)
				{
					int ind1 = TRI_TABLE[bits][i];
					int ind2 = TRI_TABLE[bits][i + 1];
					int ind3 = TRI_TABLE[bits][i + 2];
					
					VoxCoord vc[3] {
							voxCoord[ind1],
							voxCoord[ind2],
							voxCoord[ind3]
					};
					
					//Log::d(x, y, z);
					
					VoxVertex * vert[3];
					uint32 ind[3];
					vec3 pos[3];
					
					std::vector<GLuint> * indices = terrain->getChunkFromCoord(x, y, z);
					for (int j = 0; j < 3; j++)
					{
						vert[j] = &cache[vc[j].pos.x % 2][vc[j].pos.y][vc[j].pos.z][vc[j].dir];
						indices->push_back(3 * grid.rawId(vc[j].pos) + vc[j].dir);
						
						pos[j] = vc[j].pos;
						if (vc[j].dir == 0)
							pos[j].x += vert[j]->edgePos;
						
						else if (vc[j].dir == 1)
							pos[j].z += vert[j]->edgePos;
						
						else
							pos[j].y += vert[j]->edgePos;
						
					}
					
					vec3 normal = geometry::calculateNormal(pos[0], pos[1], pos[2]);
					
					for (int j = 0; j< 3; j++)
					{
						vert[j]->normal += normal;
						
						//Log::d(to_string(vert[j]->normal));
					}
					
					
					i += 3;
				}
				
			} // for z
		} // for y
		
		for (int y = 0; y < sizeY; y++)
			for (int z = 0; z < sizeZ; z++)
				for (int edge_dir = 0; edge_dir < 3; edge_dir++)
				{
					uint32 index = 3 * grid.rawId(x, y, z) + edge_dir;
					VoxVertex * vert = &cache[x % 2][y][z][edge_dir];
					
					vertices[index] = vert->pack();
					vert->normal = vec3(0, 0, 0);
				}
		
	} // for x
	
	return indCount;
}

/*
template <int size>
class VoxelChunk
{

	
public:
	VoxelChunk()
	{
	
	}
	
private:
	
	
	template <typename T>
	inline
	static
	vec3 vertInterp(const vec3 &pos1, const vec3 &pos2, T v1, T v2, T isolevel)
	{
		float mu = (isolevel - v1) / ((float) (v2 - v1));
		
		mu = max(min(mu, 0.99f), 0.01f);
		
		return mix(pos1, pos2, mu);
	}
	
	template<typename T>
	void marchingCubes(const Buffer3<T, size, size, size> &grid, T isolevel)
	{
		using namespace MCTABLES;
		
		std::vector<Vertex> vertList{};
		
		Buffer3<ivec3, 2, size, size> vertCache;
		T values[8];
		int voxVertices[12];
		
		for (int x = 0; x < grid.dimX - 1; x++)
			for (int y = 0; y < grid.dimY - 1; y++)
				for (int z = 0; z < grid.dimZ - 1; z++)
				{
					int bits = 0;
					int power = 1;
					
					
					for (int i = 0; i < 8; i++)
					{
						ivec3 vox = ivec3(x, y, z) + VOXEL_POSITION[i];
						values[i] = grid(vox.x, vox.y, vox.z);
						
						if (values[i] < isolevel)
							bits |= power;
						
						power <<= 1;
					}
					
					int edges = EDGE_TABLE[bits];
					
					if (edges == 0)
						continue;
					
					power = 1;
					
					for (int i = 0; i < 12; i++)
					{
						if (edges & power)
						{
							int v1 = EDGE_ORDER[i * 2];
							int v2 = EDGE_ORDER[i * 2 + 1];
							
							ivec3 vox = ivec3(x, y, z) + VOXEL_POSITION[v1];
							vox.x %= 2;
							
							if (!EDGE_CACHED[i] ||
								(x == 0 && (i == 3 || i == 8 || i == 7 || i == 11)) ||    // left cube face
								(y == 0 && (i == 0 || i == 1 || i == 2 || i == 3)) ||    // bottom cube face
								(z == 0 && (i == 0 || i == 9 || i == 4 || i == 8)))        // front cube face)
							{
								
								vec3 pos = vec3(x, y, z) +
												vertInterp((vec3) VOXEL_POSITION[v1], (vec3) VOXEL_POSITION[v2],
												values[v1], values[v2], isolevel);
								
								int index = (int) vertList.size();
								voxVertices[i] = index;
								vertCache(vox.x, vox.y, vox.z)[EDGE_DIR[i]] = index;
								vertList.push_back(Vertex(pos));
								
								
							}
							else
							{
								voxVertices[i] = vertCache(vox.x, vox.y, vox.z)[EDGE_DIR[i]];

							}
							
						}
						
						power <<= 1;
					}
					
					
					int i = 0;
					
					while(TRI_TABLE[bits][i] != -1)
					{
						int ind1 = TRI_TABLE[bits][i];
						int ind2 = TRI_TABLE[bits][i + 1];
						int ind3 = TRI_TABLE[bits][i + 2];
						
						int i1 = voxVertices[ind1];
						int i2 = voxVertices[ind2];
						int i3 = voxVertices[ind3];
						
						indices.push_back(i1);
						indices.push_back(i2);
						indices.push_back(i3);
						
						vec3 normal = geometry::calculateNormal(vertList[i1].position, vertList[i2].position, vertList[i3].position);
						
						vertList[i1].normal += normal;
						vertList[i2].normal += normal;
						vertList[i3].normal += normal;
						
						vertList[i1].normalLength += 1;
						vertList[i2].normalLength += 1;
						vertList[i3].normalLength += 1;
						
						i += 3;
					}
					
				}
		
		for (auto & vert: vertList)
		{
			vert.normal /= vert.normalLength;
			
			vertices.push_back(vert.position.x);
			vertices.push_back(vert.position.y);
			vertices.push_back(vert.position.z);
			
			vertices.push_back(vert.normal.x);
			vertices.push_back(vert.normal.y);
			vertices.push_back(vert.normal.z);
		}
	}
	
public:
	Buffer3<float, size, size, size> _grid{};
	
};
*/


