#include <Engine.h>
#include <Debug/Debug.h>
#include <Debug/Logging/FileLog.h>

#include <iostream>
#include <thread>

class Application : public Engine::App
{
public:
	void run() override
	{
		Engine::FileLog flog("", "debug_trace.txt");
		console.setTarget(&flog);

		srand(time(NULL));
		//Debug.setTarget(nullptr);
		console.logError("Buffer memory overflow!");
		console.logWarning("Buffer memory limit reached! Consider allocating more memory.");
		std::this_thread::sleep_for(Engine::Clock::Milliseconds(rand() % 1000));
		console.logMessage("Allocated {} bytes at {}", 1024, &console);
	}
};

Engine::App* Engine::createApp()
{
	return new Application();
}