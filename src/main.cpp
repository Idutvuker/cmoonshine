#include "system/GLFWManager.h"
#include "system/Window.h"
#include "system/Renderer.h"
#include "util/Timer.h"
#include "util/ModelLoader.h"
#include "world/FlyCamera.h"

#include <vector>
#include <memory>

Window *window;
Renderer *renderer;
Timer *timer;
Node *root;
Spatial *rotor;
FlyCamera *camera;

void process(float delta)
{
	camera->update(delta);
	rotor->transform = rotate(rotor->transform, delta, vec3(0, 0, 1));
}

void loop()
{
	while (!window->shouldClose())
	{
		double delta = timer->tick();

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
	window = GLFWManager::window;

	renderer = new Renderer();
	timer = new Timer();
	
	root = new Node();
	root->name = "ROOT";
	
	rotor = new Spatial();
	rotor->autoName();
	rotor->transform = translate(rotor->transform, vec3(0, 0, -3));
	root->addChild(rotor);
	
	/*std::vector<float> vertices = {
		-5.f, 0.f, -5.f,
		-5.f, 0.f, 5.f,
		5.f,  0.f, -5.f,
		5.f,  0.f, 5.f
	};

	std::vector<int> indices = { 0, 1, 2, 1, 2, 3};
	std::vector<VertexDataType> types = { VertexDataType::POSITION};
	
	std::shared_ptr<BaseMaterial> material(new BaseMaterial(
			"res/shaders/basic.vert",
			"res/shaders/basic.frag",
			types));
	
	auto mesh = new Mesh(vertices, indices, material);
	mesh->autoName();
	root->addChild(mesh);*/
	
	
	std::vector<VertexDataType> types2 = { VertexDataType::POSITION, VertexDataType::NORMAL};
	std::shared_ptr<BaseMaterial> material2(new BaseMaterial(
			"res/shaders/simple.vert",
			"res/shaders/simple.frag",
			types2));
	
	ModelLoader::load("res/models/monkey2.obj", rotor, material2);
	
	
	camera = new FlyCamera(1.1f, window->getWidth(), window->getHeight());
	camera->name = "Camera";
	root->addChild(camera);
	
	renderer->setCamera(camera);
	
	
	//root->recursivePrint();
	loop();
	quit();

	return 0;
}