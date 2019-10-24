#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../util/Logger.h"
#include "Window.h"
#include "Configuration.h"

namespace Engine
{
	extern bool initialized;
	extern Window *window;
	extern Configuration configuration;
	
	bool init(int windowWidth, int windowHeight, const char * title);
	
	void quit();
};


