#include <Engine.h>
#include <Debug/Debug.h>
#include <Debug/Logging/FileLog.h>

#include <Application/Window.h>
#include <Core/StackAllocator.h>

class Application : public Engine::App
{
public:
	void run() override
	{
		Engine::Window window(1280, 720, "Hello Engine!");

		Engine::StackAllocator a(16, true);
		auto x = a.alloc<TestClass>();

		while (!window.isCloseRequested())
		{
			window.t_pollEvents();
			window.swapBuffers();
		}
	}
};

Engine::App* Engine::createApp()
{
	return new Application();
}