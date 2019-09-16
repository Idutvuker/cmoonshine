#pragma once

#include "Node.h"
#include "../util/glmath.h"

class Spatial : public Node
{
public:
	MACRO_NODE_DECL()

public:
	mat4 transform = mat4(1.f);
};


