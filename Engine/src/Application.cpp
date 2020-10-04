#include "pch.h"
#include "Application.h"

namespace Engine
{

	Window Application::window;
	ThreadPool Application::asyncTaskManager;
	StackAllocator Application::singleFrameStack;
	std::mutex Application::physicsAccessMutex;
	std::unordered_map<const char*, Layer*> Application::layers;
	Clock Application::mainLoopClock;

	void Application::init()
	{
		asyncTaskManager.start(7);
		window.create(1000, 1000, "Engine");
	}

	void Application::terminate()
	{
		for (std::pair<const char*, Layer*> pair : layers)
		{
			pair.second->onClose();
		}

		asyncTaskManager.finish();
	}

	Window Application::getWindow()
	{
		return window;
	}

	void Application::run()
	{
		loadDependencies();

		asyncTaskManager.enqueue(runPhysics);

		while (!window.isCloseRequested())
		{
			singleFrameStack.clear();

			handleEvents();

			Engine::Renderer::clearActiveFramebuffer();
			beginFrame();
			endFrame();
			window.swapBuffers();
		}
	}

	void Application::pushLayer(const char* name, Layer* layer)
	{
		layers[name] = layer;
	}

	void Application::setStaticTickRate(float ms)
	{
	}

	void Application::loadDependencies()
	{
		for (std::pair<const char*, Layer*> pair : layers)
		{
			pair.second->window = &window;
			pair.second->onLoad();
		}
	}

	void Application::beginFrame()
	{
		Renderer::_renderTriangle();

		float dt = mainLoopClock.tick();
		for (std::pair<const char*, Layer*> pair : layers)
		{
			pair.second->deltaTime = dt;
			pair.second->onFrameStart();
		}
	}

	void Application::endFrame()
	{
		for (std::pair<const char*, Layer*> pair : layers)
		{
			pair.second->onFrameEnd();
		}
	}

	void Application::handleEvents()
	{
		for (const auto& event : window.pollEvents())
		{
			if (event.type == Engine::EventType::KEY_RELEASE && event.key.code == Engine::Key::ESCAPE)
				window.close();
		}
	}

	void Application::runPhysics()
	{
	}

}