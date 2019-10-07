#include "SimpleMaterial.h"

std::vector<VertexDataType> SimpleMaterial::types{ VertexDataType::POSITION,
												   VertexDataType::NORMAL};

SimpleMaterial::SimpleMaterial() :
		BaseMaterial("res/shaders/simple.vert", "res/shaders/simple.frag", types)
{}
