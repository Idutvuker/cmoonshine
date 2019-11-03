#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../util/Logger.h"
#include "Window.h"
#include "Configuration.h"
#include "Input.h"
#include "Assets.h"

namespace Engine
{
	extern Window *window;
	
	extern bool initialized;
	
	bool _init(int windowWidth, int windowHeight, const char * title);
	
	void _quit();
};


