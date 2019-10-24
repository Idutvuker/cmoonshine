#include "FlyCamera.h"
#include "../system/Engine.h"


FlyCamera::FlyCamera(float fov, int width, int height) :
		Camera(fov, width, height, 0.1f, 100.f)
{
	using namespace Engine;
	
	window->setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (Configuration::rawMouseSupported)
		window->setInputMode(GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	
	window->getCursorPos(&prevX, &prevY);
}



void FlyCamera::update(float delta) {
	using namespace Engine;
	
	double posX;
	double posY;
	
	window->getCursorPos(&posX, &posY);
	
	float dx = (float) ((posX - prevX) * sensitivity);
	float dy = (float) ((posY - prevY) * sensitivity);
	prevX = posX;
	prevY = posY;
	
	pitchMat = rotate(pitchMat, -dy, vec3(1, 0, 0));
	yawMat = rotate(yawMat, -dx, vec3(0, 1, 0));
	mat4 rotMat = yawMat * pitchMat;
	
	
	//transform = yaw * pitch;
	bool moved = false;
	vec3 moveVec(0, 0, 0);
	if (Input::keyPressed(GLFW_KEY_W)) {
		moveVec.z -= 1;
		moved = true;
	}
	if (Input::keyPressed(GLFW_KEY_S)) {
		moveVec.z += 1;
		moved = true;
	}
	if (Input::keyPressed(GLFW_KEY_A)) {
		moveVec.x -= 1;
		moved = true;
	}
	if (Input::keyPressed(GLFW_KEY_D)) {
		moveVec.x += 1;
		moved = true;
	}
	
	float speedMult = 1.f;
	
	if (window->isKeyPressed(GLFW_KEY_LEFT_SHIFT))
		speedMult = 2.f;
	
	
	if (moveVec != vec3(0, 0, 0))
	{
		moveVec = normalize(moveVec) * flySpeed * speedMult * delta;
		
		
		
		transMat = translate(transMat, mat3(rotMat) * moveVec);
	}
	
	transform = transMat * rotMat;
}
