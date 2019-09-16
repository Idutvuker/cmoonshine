#pragma once

#include <GLFW/glfw3.h>

class Timer
{
	double prevTime;

public:
	double tick();
};
