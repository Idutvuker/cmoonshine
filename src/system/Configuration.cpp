#include "Configuration.h"

namespace Engine
{
	namespace Configuration
	{
		bool useMSAA = false;
		bool wireframe = false;
		bool rawMouseSupported = false;
		bool backfaceCulling = true;
		
		void scanSystemConfig()
		{
			rawMouseSupported = (glfwRawMouseMotionSupported() == GLFW_TRUE);
		}
	}
}