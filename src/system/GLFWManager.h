#pragma once


#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <iostream>


#include "Window.h"
#include "../util/Logger.h"

class GLFWManager
{
public:
	static Window *window;

	static void keyCallback(GLFWwindow* handle, int key, int scancode, int action, int mods);

	static void errorCallback(int code, const char *decs);

	static Window * init(int windowWidth, int windowHeight, const char * title);


	static void quit();

	static bool rawMouseInputSupported();
};

