#include <Engine.h>
#include <Debug/Debug.h>
#include <Debug/Logging/FileLog.h>

#include <Application/Window.h>
#include <Core/StackAllocator.h>
#include <Core/ThreadPool.h>

#include <iostream>

//TODO: Game loop. Add both fixed timesteps and non-fixed time steps

class Application : public Engine::App
{
public:
	void run() override
	{
		
	}
};

Engine::App* Engine::createApp()
{
	return new Application();
}