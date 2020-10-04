#pragma once

#include "Event.h"

#include <GLFW/glfw3.h>
#include <vector>

namespace Engine
{

	struct Viewport
	{
		int x, y, w, h;
	};

	class Window
	{
	public:
		static GLFWglproc getGLLoadProc(const char* procname);
		static GLFWvkproc getVKLoadProc(const char* procname);

		void create(u32_t width, u32_t height, const char* title, bool fullscreen = false);
		Window() {}
		Window(u32_t width, u32_t height, const char* title, bool fullscreen = false);
		virtual ~Window();

		void updateContext();
		void swapBuffers();
		void close();
		void setTitle(const char* title);
		void setSize(u32_t width, u32_t height);
		void setViewport(const Viewport& viewport);
		void setViewport(int x, int y, int w, int h);
		void setVsyncEnabled(bool enable);
		const char* getTitle() const;
		const Viewport getViewport() const;
		const bool isCloseRequested() const;
		const std::vector<Event>& pollEvents();
		GLFWwindow* getPtr();
		//TODO: Vector2 getSize() -> returns the size of the window

	private:
		void setupGLWindow(int width, int height, const char* title, bool fullscreen);
		void setupVKWindow(int width, int height, const char* title, bool fullscreen);

		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

		const char* title;
		Viewport viewport;
		GLFWwindow* window;
		std::vector<Event> events;
	};

}