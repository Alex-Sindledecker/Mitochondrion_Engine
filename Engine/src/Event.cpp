#include "pch.h"

#include "Event.h"

extern GLFWwindow* PrimaryDisplay;

bool isKeyPressed(Key key)
{
	return glfwGetKey(PrimaryDisplay, (int)key) == GLFW_PRESS;
}

bool isKeyReleased(Key key)
{
	return glfwGetKey(PrimaryDisplay, (int)key) == GLFW_RELEASE;
}

MousePos getMousePos()
{
	MousePos p;
	glfwGetCursorPos(PrimaryDisplay, &p.x, &p.y);
	return p;
}
