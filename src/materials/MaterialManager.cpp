#include "MaterialManager.h"

#include <memory>
#include "SimpleMaterial.h"

std::shared_ptr<BaseMaterial> MaterialManager::defaultMaterial{};
std::shared_ptr<BaseMaterial> MaterialManager::wireframeMaterial{};

void MaterialManager::init()
{
	defaultMaterial = std::shared_ptr<BaseMaterial>(new SimpleMaterial());
	
	std::vector<VertexDataType> types{VertexDataType::POSITION};
	wireframeMaterial = std::make_shared<BaseMaterial>(
			"res/shaders/wireframe.vert",
			"res/shaders/wireframe.frag",
			types);
}


