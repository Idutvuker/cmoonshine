#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../util/Logger.h"
#include "Window.h"
#include "Configuration.h"
#include "Input.h"

namespace Engine
{
	extern Window *window;
	
	extern bool initialized;
	
	bool init(int windowWidth, int windowHeight, const char * title);
	
	void quit();
};


