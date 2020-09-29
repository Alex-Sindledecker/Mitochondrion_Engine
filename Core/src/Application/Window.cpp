#include "pch.h"
#include "Window.h"
#include "Debug/Debug.h"

namespace Engine
{
	GLFWwindow* PrimaryDisplay;

	constexpr u8 eventQueueCapactiy = 20;

	void Window::init()
	{
		glfwInit();
	}

	void Window::terminate()
	{
		glfwTerminate();
	}

	Window::Window(u16 width, u16 height, const char* title, bool fullscreen)
		: events(eventQueueCapactiy)
	{
		this->title = title;
		this->viewport = { 0, 0, width, height };
		if (fullscreen)
			window = glfwCreateWindow(width, height, title, glfwGetPrimaryMonitor(), nullptr);
		else
			window = glfwCreateWindow(width, height, title, nullptr, nullptr);

		if (window == nullptr)
			Debug::logError("GLFW Window creation failed! window == nullptr!");

		glfwMakeContextCurrent(window);

		glfwSetWindowUserPointer(window, this);
		glfwSetKeyCallback(window, keyCallback);
		glfwSetMouseButtonCallback(window, mouseButtonCallback);

		PrimaryDisplay = window;
	}

	Window::~Window()
	{
		glfwDestroyWindow(window);
	}

	void Window::swapBuffers()
	{
		glfwSwapBuffers(window);
		events.clear();
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

	const std::vector<Event>& Window::pollEvents()
	{
		glfwPollEvents();

		return events;
	}

	void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Event event;
		if (action == GLFW_PRESS)
			event.type = EventType::KEY_PRESS;
		else if (action == GLFW_RELEASE)
			event.type = EventType::KEY_RELEASE;
		event.key.code = (Key)key;
		event.key.alt = isKeyPressed(Key::LEFT_ALT) | isKeyPressed(Key::RIGHT_ALT);
		event.key.ctrl = isKeyPressed(Key::LEFT_CONTROL) | isKeyPressed(Key::RIGHT_CONTROL);
		event.key.shift = isKeyPressed(Key::LEFT_SHIFT) | isKeyPressed(Key::RIGHT_SHIFT);
		
		Window* w = (Window*)glfwGetWindowUserPointer(window);
		w->events.push_back(event);
	}

	void Window::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		Event event;

		if (action == GLFW_PRESS)
			event.type == EventType::MOUSE_BUTTON_PRESS;
		else if (action == GLFW_RELEASE)
			event.type == EventType::MOUSE_BUTTON_RELEASE;

		event.mouseButton.btn = (MouseButton)button;

		Window* w = (Window*)glfwGetWindowUserPointer(window);
		w->events.push_back(event);
	}
}