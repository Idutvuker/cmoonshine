#pragma once

#include "Spatial.h"

class Camera : public Spatial
{
	MACRO_NODE_DECL()

public:
	mat4 projMat;

	Camera(float fov, int width, int height, float zNear, float zFar);
};

