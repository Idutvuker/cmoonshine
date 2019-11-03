#pragma once

#include "../common/BaseMaterial.h"


namespace Assets
{
	namespace Materials
	{
		extern BaseMaterial *defaultM;
		extern BaseMaterial *wireframe;
		
		void init();
		
		void destroy();
		
		BaseMaterial *load(const BaseMaterial::Definition &def);
	}
}
