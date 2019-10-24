#pragma once


#include <GLFW/glfw3.h>

struct Configuration
{
	bool useMSAA = false;
	bool wireframe = false;
	bool rawMouseSupported;
	Configuration() = default;
	Configuration(int a);
};


