#include <Engine.h>
#include <Debug/Debug.h>

#include <iostream>
#include <thread>

class Application : public Engine::App
{
public:
	void run() override
	{
		//Debug.setTarget(nullptr);
		Debug.logError("Buffer memory overflow!");
		Debug.logWarning("Buffer memory limit reached! Consider allocating more memory.");
		std::this_thread::sleep_for(Engine::Clock::Milliseconds(rand() % 1000));
		Debug.logMessage("Allocated {} bytes at {}", 1024, &Debug);
	}
};

Engine::App* Engine::createApp()
{
	return new Application();
}