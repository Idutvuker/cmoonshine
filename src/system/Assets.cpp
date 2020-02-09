#include "Assets.h"
#include "Textures.h"

namespace Assets
{
	void init()
	{
		Materials::init();
		Textures::init();
	}
	
	void destroy()
	{
		Materials::destroy();
		Textures::destroy();
	}
}

