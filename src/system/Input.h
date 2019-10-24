#pragma once


#include <cstdint>
#include "Engine.h"

namespace Engine
{
	namespace Input
	{
		enum STATUS : uint8_t
		{
			RELEASED = 0,
			JUST_PRESSED = 1,
			PRESSED = 2,
			JUST_RELEASED = 3
		};
		
		void keyCallback(GLFWwindow *handle, int key, int scancode, int action, int mods);
		
		bool keyPressed(int key);
		bool keyJustPressed(int key);
		bool keyJustReleased(int key);
//		STATUS keyStatus();
		
		void pollEvents();
	}
}

