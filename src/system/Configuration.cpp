#include "Configuration.h"

namespace Engine
{
	namespace Configuration
	{
		bool useMSAA = false;
		bool wireframe = false;
		bool rawMouseSupported = false;
		
		
		void scanSystemConfig()
		{
			rawMouseSupported = (glfwRawMouseMotionSupported() == GLFW_TRUE);
		}
	}
}