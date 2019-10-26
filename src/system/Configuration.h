#pragma once


#include <GLFW/glfw3.h>

namespace Engine
{
	namespace Configuration
	{
		extern bool useMSAA;
		extern bool wireframe;
		extern bool rawMouseSupported;
		extern bool backfaceCulling;
		
		void scanSystemConfig();
		
		
	}
}

