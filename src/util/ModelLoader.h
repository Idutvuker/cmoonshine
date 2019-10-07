#pragma once

#include "../world/Node.h"
#include "../world/Mesh.h"
#include <string>

class ModelLoader
{
public:
	static void load(const std::string &path, Node *to, std::shared_ptr<BaseMaterial> material, float scale);

};


