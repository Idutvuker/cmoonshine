#pragma once

#include "../system/RenderContext.h"
#include "Spatial.h"
#include "Node.h"

class Drawable : public Spatial
{
	MACRO_NODE_DECL();

public:
	virtual void draw(const RenderContext &context) = 0;
};

