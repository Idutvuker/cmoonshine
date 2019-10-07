#include "Window.h"

double Window::prevx = 0.0;
double Window::prevy = 0.0;
double Window::prevt = 0.0;


int Window::getWidth() const {
	return width;
}

int Window::getHeight() const {
	return height;
}

Window::Window(GLFWwindow *windowHandle) {
	handle = windowHandle;
	glfwGetFramebufferSize(handle, &width, &height);
}

void Window::setCurPosCallback(GLFWcursorposfun posCallback)
{
	glfwSetCursorPosCallback(handle, posCallback);
}

Window::~Window() {
	glfwDestroyWindow(handle);
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
