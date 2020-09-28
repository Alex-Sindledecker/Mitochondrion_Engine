#include <Engine.h>
#include <Debug/Debug.h>
#include <Debug/Logging/FileLog.h>

#include <Application/Window.h>
#include <CoreTools/StackAllocator.h>
#include <CoreTools/ThreadPool.h>

#include <iostream>

//TODO: Game loop. Add both fixed timesteps and non-fixed time steps

class Application : public Engine::App
{
public:
	void run() override
	{
		Engine::Window window(1280, 720, "Testing...");

		while (!window.isCloseRequested())
		{
			for (auto event : window.pollEvents())
			{

			}

			window.swapBuffers();
		}
	}
};

Engine::App* Engine::createApp()
{
	return new Application();
}