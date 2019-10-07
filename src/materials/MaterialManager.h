#pragma once


#include <memory>
#include "../common/BaseMaterial.h"

class MaterialManager
{
public:
	static std::shared_ptr<BaseMaterial> defaultMaterial;
	static std::shared_ptr<BaseMaterial> wireframeMaterial;
	
	static void init();
};


