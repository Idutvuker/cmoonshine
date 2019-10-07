#include "Application.h"
#include "GLFWManager.h"
#include "../materials/MaterialManager.h"

int Application::windowWidth;
int Application::windowHeight;

bool Application::useMSAA = false;

void Application::init()
{
	GLFWManager::init(windowWidth, windowHeight, "Moonshine");
	MaterialManager::init();
}
