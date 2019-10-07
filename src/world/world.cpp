#pragma once

#include "FlyCamera.h"
#include "Mesh.h"
#include "NodeType.h"
#include "Node.h"
#include "Terrain.h"


MACRO_FIRST_NODE_IMPL(Node)
MACRO_NODE_IMPL(Spatial, Node)
MACRO_NODE_IMPL(Drawable, Spatial)
MACRO_NODE_IMPL(Mesh, Drawable)
MACRO_NODE_IMPL(Camera, Spatial)
MACRO_NODE_IMPL(FlyCamera, Camera)
MACRO_NODE_IMPL(Terrain, Drawable)