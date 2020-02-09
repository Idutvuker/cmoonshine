#pragma once
#include "../common/Texture.h"

namespace Assets
{
	namespace Textures
	{
		extern Texture *defaultT;
		
		Texture *load(const std::string &filepath);
		void init();
		void destroy();
	}
}