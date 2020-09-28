#pragma once

#include "Core.h"
#include "Event.h"

#include <GLFW/glfw3.h>
#include <vector>

namespace Engine
{

	struct ENGINE_API Viewport
	{
		int x, y, w, h;
	};
	
	class ENGINE_API Window
	{
	public:
		Window(u16 width, u16 height, const char* title, bool fullscreen = false);
		virtual ~Window();

		void swapBuffers();
		void setTitle(const char* title);
		void setSize(u16 width, u16 height);
		void setViewport(const Viewport& viewport);
		void setViewport(int x, int y, int w, int h);
		void setVsyncEnabled(bool enable);
		const char* getTitle() const;
		const Viewport getViewport() const;
		const bool isCloseRequested() const;
		const std::vector<Event>& pollEvents();
		//TODO: Vector2 getSize() -> returns the size of the window

	private:
	 	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

		const char* title;
		Viewport viewport;
		GLFWwindow* window;
		std::vector<Event> events;
	};

}