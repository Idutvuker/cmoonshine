#include "system/Engine.h"
#include "system/Window.h"
#include "system/Renderer.h"
#include "util/Timer.h"
#include "util/ModelLoader.h"
#include "world/FlyCamera.h"
#include "materials/SimpleMaterial.h"
#include "materials/MaterialManager.h"
#include "world/Terrain.h"

#include <memory>

Renderer *renderer;
Timer *timer;
Node *root;
Spatial *emp2;
Spatial *emp1;
FlyCamera *camera;
Terrain *terrain;

void picking(float val)
{
	int x = Engine::window->getWidth() / 2;
	int y = Engine::window->getHeight() / 2;
	
	
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
	using namespace Engine;
	camera->update(delta);
	
	emp1->transform = rotate(emp1->transform, delta, vec3(1, 1, 0));
	//emp2->transform = rotate(emp2->transform, delta, vec3(0, 0, 1));
	
	
	int state = window->getMouseButton(GLFW_MOUSE_BUTTON_LEFT);
	
	if (state == GLFW_PRESS)
		picking(delta);

	if (window->getMouseButton(GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		picking(-delta);
	
	if (Input::keyJustPressed(GLFW_KEY_Q))
		picking(-1.0f);
	
	if (Input::keyJustPressed(GLFW_KEY_SPACE))
	{}
	
	prevState = state;
}

void loop()
{
	using namespace Engine;
	while (!window->shouldClose())
	{
		double delta = timer->tick();
		//Log::d(1.0 / delta);
		
		
		Input::pollEvents();

		process((float) delta);

		renderer->renderWorld(root);
		window->swapBuffers();
	}
}

void quit()
{
	Engine::quit();

	delete timer;
	delete renderer;
	delete root;
}

int main()
{
	Engine::init(800, 800, "moonshine");
	using Engine::window;
	
	MaterialManager::init();
	
	renderer = new Renderer();
	timer = new Timer();
	
	root = new Node();
	root->name = "ROOT";
	
	ModelLoader::load("res/models/plane.obj", root, MaterialManager::defaultMaterial, 10.f);
	
	emp1 = new Spatial();
	emp1->transform = translate(emp1->transform, vec3(-7, 3, -3));
	root->addChild(emp1);
	
	emp2 = new Spatial();
	emp2->transform = translate(emp2->transform, vec3(0, 2, 0));
	emp1->addChild(emp2);
	
	terrain = new Terrain();
	root->addChild(terrain);
	
	ModelLoader::load("res/models/monkey2.obj", emp1, MaterialManager::defaultMaterial, 1.f);
	ModelLoader::load("res/models/teapot2.obj", emp2, MaterialManager::defaultMaterial, 0.5f);
	
	camera = new FlyCamera(1.1f, window->getWidth(), window->getHeight());
	camera->name = "Camera";
	root->addChild(camera);
	
	renderer->setCamera(camera);
	
	loop();
	quit();

	return 0;
}