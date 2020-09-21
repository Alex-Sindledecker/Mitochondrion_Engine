#include <Engine.h>
#include <Debug/Debug.h>
#include <Debug/Logging/FileLog.h>

#include <Application/Window.h>
#include <Core/StackAllocator.h>

#include <iostream>

int temp = 0;

class Application : public Engine::App
{
public:
	void run() override
	{
		Engine::Window window(1280, 720, "Hello Engine!");

		while (!window.isCloseRequested())
		{
			window.t_pollEvents();
			window.swapBuffers();
		}
	}
};

Engine::App* Engine::createApp()
{
	Logger.logMessage("Hello World!");
	return new Application();
}