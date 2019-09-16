#pragma once

#include "../util/glmath.h"

struct RenderContext
{
	mat4 Proj = IDENTITY_MATRIX;
	
	mat4 View = IDENTITY_MATRIX;
	mat4 Model = IDENTITY_MATRIX;
	mat4 ViewProj = IDENTITY_MATRIX;
};