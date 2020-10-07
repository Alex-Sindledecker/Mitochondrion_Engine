#include "pch.h"

#include "Event.h"

namespace Engine
{

	extern GLFWwindow* PrimaryDisplay;

	bool isKeyPressed(Key key)
	{
		return glfwGetKey(PrimaryDisplay, static_cast<int>(key)) == GLFW_PRESS;
	}

	bool isKeyReleased(Key key)
	{
		return glfwGetKey(PrimaryDisplay, static_cast<int>(key)) == GLFW_RELEASE;
	}

	MousePos getMousePos()
	{
		MousePos p;
		glfwGetCursorPos(PrimaryDisplay, &p.x, &p.y);
		return p;
	}

}
