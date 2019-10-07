#pragma once

#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include "../util/Logger.h"

class Window
{
	GLFWwindow *handle = nullptr;
	int width;
	int height;


public:
	
	Window(GLFWwindow *windowHandle);
	
	~Window();
	
	static double prevx;
	static double prevy;
	static double prevt;

	int getWidth() const;

	int getHeight() const;
	

	bool shouldClose() const;

	void swapBuffers() const;

	void setInputMode(int mode, int value) const;

	void getCursorPos(double *xpos, double *ypos) const;

	bool isKeyPressed(int key) const;
	
	bool getMouseButton(int button);
	
	void setCurPosCallback(GLFWcursorposfun posCallback);
};

