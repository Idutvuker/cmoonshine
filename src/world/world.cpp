#pragma once

#include "FlyCamera.h"
#include "Mesh.h"
#include "NodeType.h"
#include "Node.h"


MACRO_FIRST_NODE_IMPL(Node)
MACRO_NODE_IMPL(Spatial, Node)
MACRO_NODE_IMPL(Mesh, Spatial)
MACRO_NODE_IMPL(Camera, Spatial)
MACRO_NODE_IMPL(FlyCamera, Camera)