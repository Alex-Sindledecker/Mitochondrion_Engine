#include "mepch.h"
#include "Application.h"

namespace mito
{

	void Application::init()
	{
		windowViewport = { 0, 0, 1280, 720 };
		createWindow();

		onProgramStart();
	}
	
	void Application::terminate()
	{
		onProgramEnd();

		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void Application::run()
	{
		gameLoopClock.restart();

		while (!glfwWindowShouldClose(window))
		{
			glfwPollEvents();
			glClear(GL_COLOR_BUFFER_BIT);

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
		glfwInit();
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		window = glfwCreateWindow(windowViewport.width, windowViewport.height, "My Application", nullptr, nullptr);
		MITO_ASSERT(window != nullptr);
		glfwMakeContextCurrent(window);

		MITO_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == true);

		glClearColor(0.13f, 0.32f, 0.58f, 1.f);
	}

}