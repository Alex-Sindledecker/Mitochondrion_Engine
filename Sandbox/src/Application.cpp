#include <Engine.h>
#include <Debug/Debug.h>
#include <Debug/Logging/FileLog.h>

#include <Application/Window.h>
#include <CoreTools/StackAllocator.h>
#include <CoreTools/ThreadPool.h>

#include <iostream>

//TODO: Game loop. Add both fixed timesteps and non-fixed time steps

int main(int argc, char** argv)
{
	//Initialize core systems
	Engine::Debug::init();
	Engine::Window::init();

	Engine::Window window(1280, 720, "Testing...");

	while (!window.isCloseRequested())
	{
		for (const auto& event : window.pollEvents())
		{

		}

		window.swapBuffers();
	}


	//Terminate core systems
	Engine::Window::terminate();

	return 0;
}