#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "../util/glmath.h"
#include "../world/Node.h"
#include "../world/Mesh.h"
#include "../world/Camera.h"

#include "RenderContext.h"

class Renderer
{
private:
	std::vector<mat4> stack;
	RenderContext context;
	Camera * camera;

	void recursiveRender(Node *node, int depth);

public:
	void setCamera(Camera * aCamera);


	Renderer(int maxHeight = 40);

	void renderWorld(Node *root);
	
	void updateConfiguration();
};