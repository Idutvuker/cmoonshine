#include "Renderer.h"
#include "Application.h"

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
	stack[0] = mat4(1.0f);
	
	
	
	glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	
	if (Application::useMSAA)
		glEnable(GL_MULTISAMPLE);
	
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
}

void Renderer::renderWorld(Node *root) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	context.View = inverse(camera->transform);
	context.Proj = camera->projMat;
	context.ViewProj = context.Proj * context.View;
	context.Model = IDENTITY_MATRIX;
	
	recursiveRender(root);
}