#include "Engine.h"

namespace Engine
{
	Window *window;
	Configuration configuration{};
	bool initialized = false;
	
	//private callbacks
	namespace
	{
		void keyCallback(GLFWwindow *handle, int key, int scancode, int action, int mods) {
			if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
				glfwSetWindowShouldClose(handle, GLFW_TRUE);
		}
		
		void errorCallback(int code, const char *decs) {
			Log::e("Error callback: ");
			Log::e(decs);
		}
		
		void scanSystemConfig()
		{
			configuration.rawMouseSupported = (glfwRawMouseMotionSupported() == GLFW_TRUE);
		}
	}
	
	
	
	void quit()
	{
		delete window;
		glfwTerminate();
	}
	
	bool init(int windowWidth, int windowHeight, const char *title)
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
		
		if (configuration.useMSAA)
			glfwWindowHint(GLFW_SAMPLES, 4);
		
		window = new Window(windowWidth, windowHeight, title);
		if (!window->initialized)
			return false;
		
		window->makeContextCurrent();
		window->setKeyCallback(keyCallback);
		
		
		glfwSwapInterval(0);
		
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			Log::e("Failed to initialize GLEW\n");
			return false;
		}
		
		
		scanSystemConfig();
		
		initialized = true;
		return true;
	}
}