#pragma once


#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>


class Window
{
	GLFWwindow *handle = nullptr;
	int width = 0;
	int height = 0;
	
public:
	const bool initialized;
	
	Window(int windowWidth, int windowHeight, const char *title);
	~Window();
	
	int getWidth() const;

	int getHeight() const;
	

	bool shouldClose() const;

	void swapBuffers() const;

	void setInputMode(int mode, int value) const;

	void getCursorPos(double *xpos, double *ypos) const;

	bool isKeyPressed(int key) const;
	
	bool getMouseButton(int button);
	
	void makeContextCurrent();
	
	
	void setCurPosCallback(GLFWcursorposfun posCallback);
	void setKeyCallback(GLFWkeyfun callback);
	
//	friend bool Engine::init(int, int, const char *);
//	friend void Engine::quit();
};
