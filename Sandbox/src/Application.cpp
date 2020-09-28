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
		Engine::ThreadPool tp(4);

		std::future<int> val = tp.enqueue(getValue, 5, 6);

		while (true)
		{
			if (Engine::futureIsReady(val))
				std::cout << val.get() << std::endl;

			Logger.logMessage("Program running...");
		}
	}

	static int getValue(int a, int b)
	{
		std::this_thread::sleep_for(Engine::Seconds(5));
		return a + b;
	}
};

Engine::App* Engine::createApp()
{
	return new Application();
}