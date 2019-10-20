#include "MaterialManager.h"

#include <memory>
#include "SimpleMaterial.h"

std::shared_ptr<BaseMaterial> MaterialManager::defaultMaterial{};
std::shared_ptr<BaseMaterial> MaterialManager::wireframeMaterial{};

void MaterialManager::init()
{
	BaseMaterial::Definition def;
	def.vertexShaderFilepath = "res/shaders/simple.vert";
	def.fragmentShaderFilepath = "res/shaders/simple.frag";
	defaultMaterial = std::make_shared<BaseMaterial>(def);
	
	def.vertexShaderFilepath = "res/shaders/wireframe.vert";
	def.fragmentShaderFilepath = "res/shaders/wireframe.frag";
	wireframeMaterial = std::make_shared<BaseMaterial>(def);
}


