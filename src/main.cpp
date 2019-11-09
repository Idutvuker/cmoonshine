#include "system/Engine.h"
#include "system/Window.h"
#include "system/Renderer.h"
#include "util/Timer.h"
#include "util/ModelLoader.h"
#include "world/FlyCamera.h"
#include "world/Terrain.h"

#include <memory>

Renderer *renderer;
Timer *timer;
Node *root;
Spatial *emp2;
Spatial *emp1;
FlyCamera *camera;
Terrain *terrain;

float radius = 3;

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
		t = inverse(terrain->transform) * t;
		
		vec3 r = vec3(t) / t.w;
		terrain->change(r, val, radius);
		
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
	{
		Configuration::wireframe ^= true;
		renderer->updateConfiguration();
	}
	
	if (Input::keyJustPressed(GLFW_KEY_E))
	{
		terrain->switchShading();
	}
	
	if (Input::keyPressed(GLFW_KEY_1))
		radius += 4 * delta;
	
	if (Input::keyPressed(GLFW_KEY_2))
	{
		radius -= 4 * delta;
		if (radius < 0)
			radius = 0;
	}
	
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
	Engine::_quit();

	delete timer;
	delete renderer;
	delete root;
}

int main()
{
	Engine::_init(900, 900, "moonshine");
	using namespace Engine;
	Assets::init();
	
	renderer = new Renderer();
	timer = new Timer();
	
	root = new Node();
	root->name = "ROOT";
	
	ModelLoader::load("res/models/plane.obj", root, Assets::Materials::defaultM, 10.f);
	
	emp1 = new Spatial();
	emp1->transform = translate(emp1->transform, vec3(-7, 3, -3));
	root->addChild(emp1);
	
	emp2 = new Spatial();
	emp2->transform = translate(emp2->transform, vec3(0, 2, 0));
	emp1->addChild(emp2);
	
	terrain = new Terrain();
	terrain->transform = translate(scale(IDENTITY_MATRIX, vec3(0.3f, 0.3f, 0.3f)), vec3(-32, -1, -32));
	root->addChild(terrain);
	
	BaseMaterial::Definition def;
	def.vertexShaderFilepath = "res/shaders/simple.vert";
	def.fragmentShaderFilepath = "res/shaders/simple.frag";
	def.defines = {"TEXTURED"};
	
	auto mat = new BaseMaterial(def);
	auto tx = new Texture("res/textures/default.png");
	mat->setTexture("tex", tx);
	
	ModelLoader::load("res/models/monkey2.obj", emp1, mat, 1.f);
	ModelLoader::load("res/models/teapot2.obj", emp2, Assets::Materials::defaultM, 0.5f);
	
	camera = new FlyCamera(1.1f, window->getWidth(), window->getHeight());
	camera->name = "Camera";
	root->addChild(camera);
	
	renderer->setCamera(camera);
	
	loop();
	quit();

	return 0;
}