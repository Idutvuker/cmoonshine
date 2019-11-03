#include "Engine.h"

namespace Engine
{
	Window *window;

	bool initialized = false;
	
	//private callbacks
	namespace
	{
		void errorCallback(int code, const char *decs) {
			Log::e("Error callback: ");
			Log::e(decs);
		}
	}
	
	
	
	void _quit()
	{
		Assets::destroy();
		delete window;
		
		glfwTerminate();
	}
	
	bool _init(int windowWidth, int windowHeight, const char *title)
	{
		
//		GLenum error = glGetError();
//
//		if (error != GL_NO_ERROR) {
//			Log::e("OpenGL Error:", error);
//		}
		
		if (glfwInit() == GLFW_FALSE)
		{
			Log::e("Failed to initialize GLFW\n");
			return false;
		}
		
		glfwSetErrorCallback(errorCallback);
		
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		
		if (Configuration::useMSAA)
			glfwWindowHint(GLFW_SAMPLES, 4);
		
		window = new Window(windowWidth, windowHeight, title);
		if (!window->initialized)
			return false;
		
		window->makeContextCurrent();
		window->setKeyCallback(Input::keyCallback);
		
		
		glfwSwapInterval(0);
		
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			Log::e("Failed to initialize GLEW\n");
			return false;
		}
		
		
		Configuration::scanSystemConfig();
		
		initialized = true;
		return true;
	}
}