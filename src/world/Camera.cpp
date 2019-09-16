#include "Camera.h"



Camera::Camera(float fov, int width, int height, float zNear, float zFar) :
		projMat(perspectiveFov(fov, (float) width, (float) height, zNear, zFar))
{}


