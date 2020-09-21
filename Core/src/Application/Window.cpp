#include "pch.h"
#include "Window.h"
#include "Debug/DebugTools.h"

namespace Engine
{

	Window::Window(u16 width, u16 height, const char* title, bool fullscreen)
	{
		this->title = title;
		this->viewport = { 0, 0, width, height };
		if (fullscreen)
			window = glfwCreateWindow(width, height, title, glfwGetPrimaryMonitor(), nullptr);
		else
			window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, this);
		setVsyncEnabled(true);
		glfwSetKeyCallback(window, keyCallback);
	}

	Window::~Window()
	{
		glfwDestroyWindow(window);
	}

	void Window::swapBuffers() const
	{
		glfwSwapBuffers(window);
	}

	void Window::setTitle(const char* title)
	{
		this->title = title;
	}

	void Window::setSize(u16 width, u16 height)
	{
		viewport.w = width;
		viewport.h = height;
	}

	void Window::setViewport(const Viewport& viewport)
	{
		this->viewport = viewport;
	}

	void Window::setViewport(int x, int y, int w, int h)
	{
		this->viewport = { x, y, w, h };
	}

	void Window::setVsyncEnabled(bool enable)
	{
		if (enable)
			glfwSwapInterval(1); //TODO: Find monitor refresh rate and set the swap interval to that instead
		else
			glfwSwapInterval(0);
	}

	const char* Window::getTitle() const
	{
		return title;
	}

	const Viewport Window::getViewport() const
	{
		return viewport;
	}

	const bool Window::isCloseRequested() const
	{
		return glfwWindowShouldClose(window);
	}

	void Window::t_pollEvents()
	{
		glfwPollEvents();
	}

	void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		
	}

}