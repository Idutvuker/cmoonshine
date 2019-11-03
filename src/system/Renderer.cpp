#include "Renderer.h"
#include "Engine.h"

void Renderer::recursiveRender(Node *node, int depth = 1) {
	context.Model = stack[depth - 1];
	
	if (Spatial * spatial = node->instanceOf<Spatial>())
	{
		context.Model = context.Model * spatial->transform;
		if (Drawable * drawable = node->instanceOf<Drawable>())
		{
			drawable->draw(context);
		}
	}
	
	if (depth > stack.size())
		stack.push_back(context.Model);
	else
		stack[depth] = context.Model;
	
	for (auto child : node->children)
	{
		recursiveRender(child, depth + 1);
	}
}

void Renderer::setCamera(Camera *aCamera) {
	camera = aCamera;
}

Renderer::Renderer(int maxHeight) :
	stack(maxHeight)
{
	using namespace Engine;
	
	stack[0] = mat4(1.0f);
	
	
	glViewport(0, 0, window->getWidth(), window->getHeight());
	glEnable(GL_DEPTH_TEST);
	
	updateConfiguration();
	
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
}

void Renderer::updateConfiguration()
{
	using namespace Engine;
	if (Configuration::backfaceCulling)
	{
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
	}
	
	if (Configuration::useMSAA)
		glEnable(GL_MULTISAMPLE);
	
	if (Configuration::wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void Renderer::renderWorld(Node *root) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	context.View = inverse(camera->transform);
	context.Proj = camera->projMat;
	context.ViewProj = context.Proj * context.View;
	context.Model = IDENTITY_MATRIX;
	
	recursiveRender(root);
}