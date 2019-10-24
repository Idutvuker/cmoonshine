#include "Application.h"
#include "../materials/MaterialManager.h"
#include "Engine.h"

int Application::windowWidth;
int Application::windowHeight;

bool Application::useMSAA = false;
bool Application::wireframe = false;

void Application::init()
{
	Engine::init(windowWidth, windowHeight, "Moonshine");
	
	//GLFWManager::init(windowWidth, windowHeight, "Moonshine");
	MaterialManager::init();
}
