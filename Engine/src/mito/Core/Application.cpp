#include "mepch.h"
#include "Application.h"

#include "mito-platform/OpenGL/GLCore.h"

namespace mito
{

	void Application::init()
	{
		windowViewport = { 0, 0, 1280, 720 };
		createWindow();
	}
	
	void Application::terminate()
	{
		onProgramEnd();

		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void Application::run()
	{
		onProgramStart();

		gameLoopClock.restart();

		while (!glfwWindowShouldClose(window))
		{
			glfwPollEvents();
			gl::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			deltaTime = gameLoopClock.tick();

			

			beginFrame();
			endFrame();

			glfwSwapBuffers(window);

			EventManager::_clearEventQueue();
		}
	}

	GLFWwindow* Application::getWindowPtr()
	{
		return window;
	}

	void Application::attachLayer(const char* name)
	{
		layers[name]->onAttach();
	}

	void Application::detachLayer(const char* name)
	{
		layers[name]->onDetach();
	}

	void Application::deleteLayer(const char* name)
	{
		layers.erase(name);
	}

	void Application::onProgramStart() {}

	void Application::beginFrame() {}

	void Application::endFrame() {}

	void Application::onProgramEnd() {}

	void Application::createWindow()
	{
		auto version = gl::getGLVersion();

		glfwInit();
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, version.major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, version.minor);
		window = glfwCreateWindow(windowViewport.width, windowViewport.height, "My Application", nullptr, nullptr);
		MITO_ASSERT(window != nullptr);
		glfwMakeContextCurrent(window);
	}

}