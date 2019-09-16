#pragma once

#include <vector>

struct MeshData
{
	std::vector<float> vertices;
	std::vector<int> indices;
	bool batched = false;
};


