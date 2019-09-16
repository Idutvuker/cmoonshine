#include "SimpleMaterial.h"

std::vector<VertexDataType> SimpleMaterial::types{ VertexDataType::POSITION,
												   VertexDataType::NORMAL,
												   VertexDataType::TEXCOORD };

SimpleMaterial::SimpleMaterial() :
		BaseMaterial("res/shaders/simple.vert", "res/shaders/simple.frag", types)
{}
