#include "mepch.h"
#include "Window.h"

Window::Window(uint32_t width, uint32_t height, const char* title)
{
	glfwInit();
	setWindowHints();
	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	glfwMakeContextCurrent(window);
}

Window::Window(const char* title)
{
	glfwInit();
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
	setWindowHints();
	window = glfwCreateWindow(800, 600, title, nullptr, nullptr);
	glfwMakeContextCurrent(window);
}

Window::~Window()
{
}

void Window::close()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

Viewport Window::getViewport()
{
	Viewport viewport;
	glfwGetWindowPos(window, &viewport.x, &viewport.y);
	viewport.width = width;
	viewport.height = height;
	return viewport;
}

glm::vec2 Window::getSize()
{
	return { width, height };
}

bool Window::shouldClose()
{
	return glfwWindowShouldClose(window);
}

void Window::setWindowHints()
{
#ifdef USE_VULKAN
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
#else
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#endif
}
