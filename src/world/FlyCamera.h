#pragma once

#include "Camera.h"
#include "../util/glmath.h"

class FlyCamera: public Camera
{
	MACRO_NODE_DECL()

private:
	double prevX;
	double prevY;

public:

	FlyCamera(float fov, int width, int height);

	const double sensitivity = 0.001;
	const float flySpeed = 8.0f;
	
	bool mouseLook = true;

	mat4 pitchMat = IDENTITY_MATRIX;
	mat4 yawMat = IDENTITY_MATRIX;
	mat4 transMat = IDENTITY_MATRIX;

	void update(float delta);

};
