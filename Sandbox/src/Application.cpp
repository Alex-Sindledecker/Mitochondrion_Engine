#include <iostream>
#include <Engine.h>
#include <Application/EntryPoint.h>
#include <Debug/Debug.h>

class Application : public Engine::App
{
public:
	void run() override
	{
		Engine::Debug& debug = Engine::Debug::getInstance();
		debug.logError("Buffer memory overflow!");
		debug.logWarning("Buffer memory limit reached! Consider allocating more memory.");
		debug.logMessage("Allocated {} bytes at {}", 1024, &debug);
	}


};

Engine::App* Engine::createApp()
{
	return new Application();
}