#include "GLFWManager.h"

void GLFWManager::keyCallback(GLFWwindow* handle, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(handle, GLFW_TRUE);
}

Window * GLFWManager::window = nullptr;

void GLFWManager::errorCallback(int code, const char *decs) {
	Log::e("Error callback: ");
	Log::e(decs);
}

bool GLFWManager::rawMouseInputSupported() {
	return glfwRawMouseMotionSupported();
}

void GLFWManager::quit() {
	delete window;
	glfwTerminate();
}

Window *GLFWManager::init(int windowWidth, int windowHeight, const char *title) {
	if (glfwInit() == GLFW_FALSE)
	{
		Log::e("Failed to initialize GLFW\n");
		return nullptr;
	}
	
	glfwSetErrorCallback(errorCallback);
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
	//glfwWindowHint(GLFW_SAMPLES, 4);
	
	GLFWwindow *handle = glfwCreateWindow(windowWidth, windowHeight, title, nullptr, nullptr);
	if (handle == nullptr)
	{
		Log::e("Couldn't create window\n");
		return nullptr;
	}
	
	
	
	window = new Window(handle);
	glfwMakeContextCurrent(handle);
	glfwSetKeyCallback(handle, keyCallback);
	
	glfwSwapInterval(1);
	/*GLenum error = glGetError();

	if (error != GL_NO_ERROR) {
		Log::e("OpenGL Error:", error);
	}*/
	
	glViewport(0, 0, window->getWidth(), window->getHeight());
	
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		Log::e("Failed to initialize GLEW\n");
		return nullptr;
	}
	
	return window;
}
