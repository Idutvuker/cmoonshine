#include "Input.h"


namespace Engine
{
	namespace Input
	{
		
		namespace
		{
			STATUS keys[GLFW_KEY_LAST + 1]{RELEASED};
		}
		
		void keyCallback(GLFWwindow *handle, int key, int scancode, int action, int mods)
		{
			if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
				glfwSetWindowShouldClose(handle, GLFW_TRUE);
			
			if (key == GLFW_KEY_UNKNOWN)
				return;
			
			int prev = keys[key];
			if (action == GLFW_RELEASE)
				keys[key] = JUST_RELEASED;
			
			if (action == GLFW_PRESS)
				keys[key] = JUST_PRESSED;
			
		}
		
		void pollEvents()
		{
			for (auto & key : keys)
			{
				if (key == JUST_PRESSED)
					key = PRESSED;

				if (key == JUST_RELEASED)
					key = RELEASED;
			}
			
			glfwPollEvents();
		}
		
		bool keyPressed(int key) {
			return (keys[key] == PRESSED || keys[key] == JUST_PRESSED);
		}
		
		bool keyJustPressed(int key) {
			return keys[key] == JUST_PRESSED;
		}
		
		bool keyJustReleased(int key) {
			return keys[key] == JUST_RELEASED;
		}
		
	}
}