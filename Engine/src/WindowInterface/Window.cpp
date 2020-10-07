#include "pch.h"

#include "Window.h"
#include <Debug/Debug.h>

namespace Engine
{

	GLFWwindow* PrimaryDisplay;

	constexpr u32_t eventQueueCapactiy = 20;

	GLFWglproc Window::getGLLoadProc(const char* procname)
	{
		return glfwGetProcAddress(procname);
	}

	GLFWvkproc Window::getVKLoadProc(const char* procname)
	{
		return glfwGetProcAddress(procname);
	}

	void Window::create(u32_t width, u32_t height, const char* title, bool fullscreen)
	{
		glfwInit();

		#ifdef ENGINE_USE_VULKAN
				setupVKWindow(width, height, title, fullscreen);
		#else
				setupGLWindow(width, height, title, fullscreen);
		#endif
	}

	Window::Window(u32_t width, u32_t height, const char* title, bool fullscreen)
		: events(eventQueueCapactiy)
	{
		glfwInit();

		#ifdef ENGINE_USE_VULKAN
			setupVKWindow(width, height, title, fullscreen);
		#else
			setupGLWindow(width, height, title, fullscreen);
		#endif
	}

	Window::~Window()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void Window::updateContext()
	{
		glfwMakeContextCurrent(window);
	}

	void Window::swapBuffers()
	{
		glfwSwapBuffers(window);
		events.clear();
	}

	void Window::close()
	{
		glfwSetWindowShouldClose(window, true);
	}

	void Window::setTitle(const char* title)
	{
		this->title = title;
	}

	void Window::setSize(u32_t width, u32_t height)
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

	GLFWwindow* Window::getPtr()
	{
		return window;
	}

	void Window::setupGLWindow(int width, int height, const char* title, bool fullscreen)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		this->title = title;
		this->viewport = { 0, 0, static_cast<int>(width), static_cast<int>(height) };
		if (fullscreen)
			window = glfwCreateWindow(width, height, title, glfwGetPrimaryMonitor(), nullptr);
		else
			window = glfwCreateWindow(width, height, title, nullptr, nullptr);

		if (window == nullptr)
			Engine::Debug::logError("GLFW Window creation failed! window == nullptr!");

		glfwMakeContextCurrent(window);

		glfwSetWindowUserPointer(window, this);
		glfwSetKeyCallback(window, keyCallback);
		glfwSetMouseButtonCallback(window, mouseButtonCallback);

		PrimaryDisplay = window;
	}

	void Window::setupVKWindow(int width, int height, const char* title, bool fullscreen)
	{
		Engine::Debug::logWarning("Vulkan is not yet supported! Defaulting to opengl...");
	}

	void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Event event;
		if (action == GLFW_PRESS)
			event.type = EventType::KEY_PRESS;
		else if (action == GLFW_RELEASE)
			event.type = EventType::KEY_RELEASE;
		event.key.code = static_cast<Key>(key);
		event.key.alt = isKeyPressed(Key::LEFT_ALT) | isKeyPressed(Key::RIGHT_ALT);
		event.key.ctrl = isKeyPressed(Key::LEFT_CONTROL) | isKeyPressed(Key::RIGHT_CONTROL);
		event.key.shift = isKeyPressed(Key::LEFT_SHIFT) | isKeyPressed(Key::RIGHT_SHIFT);

		Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));
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

		Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));
		w->events.push_back(event);
	}

}