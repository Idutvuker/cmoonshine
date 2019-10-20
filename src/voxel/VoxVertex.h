#pragma once

#include "../util/glmath.h"
#include <glm/gtx/norm.hpp>

typedef uint32_t PackedVoxVertex;

struct VoxVertex
{
	float edgePos = 0;
	vec3 normal{0, 0, 0};
	
	PackedVoxVertex pack()
	{
		if (normal != vec3(0, 0, 0))
		{
			//Log::d(to_string(normal));
			normal = normalize(normal);
		}
		
		
		uint32_t n_x = (uint32_t)((normal.x + 1.f) * 1023 + 0.5f);
		uint32_t n_y = (uint32_t)((normal.y + 1.f) * 1023 + 0.5f);
		//uint32_t n_z = (normal.z + 1) * 127 + 0.5f;
		
		
		
		uint32_t pos = (uint32_t)(edgePos * 255.f + 0.5f);
		
//		PackedVoxVertex res =
//							(pos << 24) +
//							(n_x << 16) +
//							(n_y << 8) +
//							(n_z);
		
		uint32_t n_neg_z = signbit(normal.z);

		PackedVoxVertex res =
							(pos << 24) +
							(n_neg_z << 23) +
							(n_x << 11) +
							(n_y);
		
		return res;
	}
};