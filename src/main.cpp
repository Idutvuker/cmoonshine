#include "system/GLFWManager.h"
#include "system/Window.h"
#include "system/Renderer.h"
#include "util/Timer.h"
#include "util/ModelLoader.h"
#include "world/FlyCamera.h"
#include "materials/SimpleMaterial.h"
#include "materials/MaterialManager.h"
#include "world/Terrain.h"

#include <vector>
#include <memory>

Window *window;
Renderer *renderer;
Timer *timer;
Node *root;
Spatial *rotor;
FlyCamera *camera;
Terrain *terrain;

void picking(float val)
{
	int x = GLFWManager::window->getWidth() / 2;
	int y = GLFWManager::window->getHeight() / 2;
	
	
	float depth;
	glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
	
	if (depth < 1.f)
	{
		vec4 t(0, 0, depth * 2.f - 1.f, 1.f);
		
		t = inverse(camera->projMat) * t;
		t = camera->transform * t;
		
		vec3 r = vec3(t) / t.w;
		terrain->change(r, val);
		
		//rotor->transform = translate(IDENTITY_MATRIX, r);
	}
	
	
}

int prevState = GLFW_RELEASE;
void process(float delta)
{
	camera->update(delta);
	//rotor->transform = rotate(rotor->transform, delta, vec3(0, 0, 1));
	
	
	int state = window->getMouseButton(GLFW_MOUSE_BUTTON_LEFT);
	
	if (state == GLFW_PRESS)
		picking(delta);

	if (window->getMouseButton(GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		picking(-delta);
	
	prevState = state;
}

void loop()
{
	while (!window->shouldClose())
	{
		double delta = timer->tick();
		//Log::d(1.0 / delta);
		
		
		glfwPollEvents();

		process((float) delta);

		renderer->renderWorld(root);
		window->swapBuffers();
	}
}

void quit()
{
	GLFWManager::quit();

	delete timer;
	delete renderer;
	delete root;
}

int main()
{
	GLFWManager::init(700, 700, "moonshine");
	MaterialManager::init();
	
	window = GLFWManager::window;

	renderer = new Renderer();
	timer = new Timer();
	
	root = new Node();
	root->name = "ROOT";
	
	rotor = new Spatial();
	rotor->autoName();
	rotor->transform = translate(rotor->transform, vec3(0, 0, -4));
	root->addChild(rotor);
	
	terrain = new Terrain();
	root->addChild(terrain);
	
	ModelLoader::load("res/models/cube.obj", rotor, MaterialManager::defaultMaterial, 0.1f);
	
	camera = new FlyCamera(1.1f, window->getWidth(), window->getHeight());
	camera->name = "Camera";
	root->addChild(camera);
	
	renderer->setCamera(camera);
	
	loop();
	quit();

	return 0;
}