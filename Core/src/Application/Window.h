#pragma once

#include "Core/Core.h"

#include <GLFW/glfw3.h>
#include <queue>

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

		void swapBuffers() const;
		void setTitle(const char* title);
		void setSize(u16 width, u16 height);
		void setViewport(const Viewport& viewport);
		void setViewport(int x, int y, int w, int h);
		void setVsyncEnabled(bool enable);
		const char* getTitle() const;
		const Viewport getViewport() const;
		const bool isCloseRequested() const;
		//TODO: Vector2 getSize() -> returns the size of the window

		void t_pollEvents();

	private:
	 	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

		const char* title;
		Viewport viewport;
		GLFWwindow* window;
	};

}