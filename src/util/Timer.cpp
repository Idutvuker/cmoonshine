#include "Timer.h"

double Timer::tick() {
	double pt = prevTime;
	return (prevTime = glfwGetTime()) - pt;
}
