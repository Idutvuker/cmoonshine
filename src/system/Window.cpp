#include "Window.h"
#include "../util/Logger.h"


int Window::getWidth() const {
	return width;
}

int Window::getHeight() const {
	return height;
}

Window::~Window() {
	glfwDestroyWindow(handle);
}

Window::Window(int windowWidth, int windowHeight, const char *title) :
	initialized(true)
{
	handle = glfwCreateWindow(windowWidth, windowHeight, title, nullptr, nullptr);
	
	if (handle == nullptr)
	{
		Log::e("Couldn't create window\n");
		return;
	}
	
	glfwGetFramebufferSize(handle, &width, &height);
}

void Window::setCurPosCallback(GLFWcursorposfun posCallback) {
	glfwSetCursorPosCallback(handle, posCallback);
}

bool Window::shouldClose() const {
	return (GLFW_TRUE == glfwWindowShouldClose(handle));
}

void Window::swapBuffers() const {
	glfwSwapBuffers(handle);
}

void Window::setInputMode(int mode, int value) const {
	glfwSetInputMode(handle, mode, value);
}

void Window::getCursorPos(double *xpos, double *ypos) const {
	glfwGetCursorPos(handle, xpos, ypos);
}

bool Window::isKeyPressed(int key) const {
	return glfwGetKey(handle, key) == GLFW_PRESS;
}

bool Window::getMouseButton(int button) {
	return glfwGetMouseButton(handle, button) == GLFW_PRESS;
}

void Window::setKeyCallback(GLFWkeyfun callback) {
	glfwSetKeyCallback(handle, callback);
}

void Window::makeContextCurrent() {
	glfwMakeContextCurrent(handle);
}


