#pragma once

#include "VoxVertex.h"
#include "Buffer3.h"
#include "MCTables.h"
#include "../util/geometry.h"

namespace MarchingCubes
{

	template <typename T>
	float interp(T val1, T val2, T isolevel)
	{
		return (isolevel - val1)/((float)(val2 - val1));
	}
	
	template<typename T, int sizeX, int sizeY, int sizeZ>
	void preMarchingCubes(
			const Buffer3<T, sizeX, sizeY, sizeZ> &grid,
			T isolevel,
			std::vector<uint32> &indices,
			const ivec3 &from,
			const ivec3 &to)
	{
		using namespace MCTABLES;
		
		T values[8];
		
		int EDGE_OFFSET[12] = {
				0,			3 * sizeZ * sizeY + 1,				3,							1,
				3 * sizeZ,	3 * sizeZ * sizeY + 3 * sizeZ + 1,	3 * sizeZ + 3,				3 * sizeZ + 1,
				2,			3 * sizeZ * sizeY + 2,				3 * sizeZ * sizeY + 3 + 2,	3 + 2
		};
		
		static VoxVertex cache[sizeX][sizeY][sizeZ][3] = {};
		//Log::d(sizeof(cache));
		
		
		vec3 vertPos[12];
		//for (int i = 0; i < 12; i++)
		//	vertPos[i] = vec3(0, 0, 0);
		
		for (int x = from.x; x < to.x; x++)
		{
			for (int y = from.y; y < to.y; y++)
			{
				for (int z = from.z; z < to.z; z++)
				{
					
					
					
					int bits = 0;
					int power = 1;
					
					
					for (int i = 0; i < 8; i++)
					{
						ivec3 vox = ivec3(x, y, z) + VOXEL_POSITION[i];
						values[i] = grid(vox.x, vox.y, vox.z);
						//Log::d(values[i]);
						if (values[i] < isolevel)
							bits |= power;
						
						power <<= 1;
					}
					
					int edges = EDGE_TABLE[bits];
					
					if (edges == 0)
						continue;
						
					uint32 id = grid.rawId(x, y, z);
					indices.push_back(id);
					glBufferSubData(GL_ARRAY_BUFFER, id * sizeof(GLint), sizeof(GLint), &bits);
					
					
					power = 1;
					
					for (int i = 0; i < 12; i++)
					{
						if (edges & power)
						{
							int v1 = EDGE_ORDER[i * 2];
							int v2 = EDGE_ORDER[i * 2 + 1];
							
							ivec3 vox = ivec3(x, y, z) + VOXEL_POSITION[v1];
							uint32 index = 3 * grid.rawId(vox) + EDGE_DIR[i];
							
							
							if (!EDGE_CACHED[i] ||
								(x == 0 && (i == 3 || i == 8 || i == 7 || i == 11)) ||    // left cube face
								(y == 0 && (i == 0 || i == 1 || i == 2 || i == 3)) ||    // bottom cube face
								(z == 0 && (i == 0 || i == 9 || i == 4 || i == 8)))        // front cube face)
							{
								float alpha = interp(values[v1], values[v2], isolevel);
								VoxVertex &vert = cache[vox.x][vox.y][vox.z][EDGE_DIR[i]];
								vert.edgePos = alpha;
								vert.normal = vec3(0, 0, 0);
								//Log::d("Write to ", index, to_string(vox));
								
								vertPos[i] = vox;
								
								if (EDGE_DIR[i] == 0)
									vertPos[i].x += alpha;
								else if (EDGE_DIR[i] == 1)
									vertPos[i].z += alpha;
								else
									vertPos[i].y += alpha;
								
								//Log::d("f", to_string(vertPos[i]), i, EDGE_DIR[i]);
							}
						}
						
						power <<= 1;
					}
					
					
					int i = 0;
	
					while (TRI_TABLE[bits][i] != -1)
					{
						int ind[3] = {
							TRI_TABLE[bits][i],
							TRI_TABLE[bits][i + 1],
							TRI_TABLE[bits][i + 2]
						};
	
						int dir[3];
						ivec3 vox[3];
						vec3 pos[3];
						VoxVertex * vert[3];
						
						//Log::d("TRIANGLE", i / 3, x, y, z, "edges:", ind[0], ind[1], ind[2]);
						for (int j = 0; j < 3; j++)
						{
							dir[j] = EDGE_DIR[ind[j]];
							vox[j] = ivec3(x, y, z) + VOXEL_POSITION[EDGE_ORDER[2 * ind[j]]];
							pos[j] = vox[j];
							
							
							
							vert[j] = &cache[vox[j].x][vox[j].y][vox[j].z][dir[j]];
							
							float alpha = vert[j]->edgePos;
							pos[j][XZYtoXYZ[EDGE_DIR[ind[j]]]] += alpha;
	//						if (EDGE_DIR[i] == 0)
	//							pos[j].x += alpha;
	//						else if (EDGE_DIR[i] == 1)
	//							pos[j].z += alpha;
	//						else
	//							pos[j].y += alpha;
							
							if (pos[j] == vec3(0, 0, 0))
							{
								int index = 3 * grid.rawId(vox[j]) + EDGE_DIR[i];
								//Log::d("zero", ind[j], alpha, index);
							}
						}
						
						
						vec3 normal = geometry::calculateNormal(pos[0], pos[1], pos[2]);
						//Log::d("Normal", to_string(normal), to_string(pos[0]), to_string(pos[1]), to_string(pos[2]));
						for (int j = 0; j < 3; j++)
						{
							//Log::d(to_string(pos[j]), to_string(vox[j]));
							//Log::d(to_string(normal));
							vert[j]->normal += normal;
							
							//Log::d(to_string(vert[j]->normal));
						}
	
	
						i += 3;
					}
					
					
				}//for z
			}// for y
		}// for x
		
		for (int x = from.x; x < to.x; x++)
			for (int y = from.y; y < to.y; y++)
				for (int z = from.z; z < to.z; z++)
				{
					for (int i = 0; i < 3; i++)
					{
						if (
								((i == 1 || i == 2) && x == from.x) ||
								((i == 0 || i == 1) && y == from.y) ||
								((i == 0 || i == 2) && z == from.z))
							continue;
				
							
							
							//ivec3 vox = ivec3(x, y, z) + VOXEL_POSITION[v1];
							uint32 index = 3 * grid.rawId(x, y, z) + i;
							VoxVertex *vert = &cache[x][y][z][i];
							
							
							
							uint32 packed = vert->pack();
							glBufferSubData(GL_TEXTURE_BUFFER, (index) * sizeof(GLuint), sizeof(GLuint), &packed);
							//vert->normal = vec3(0, 0, 0);
						//}
					}
				}
	}
}