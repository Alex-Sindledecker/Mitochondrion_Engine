#include <iostream>
#include <Engine.h>
#include <Application/EntryPoint.h>
#include <Debug/Debug.h>

class Application : public Engine::App
{
public:
	void run() override
	{
		Debug.setLevel(Debug.LOG_MESSAGE | Debug.LOG_ERROR);
		//Debug.setTarget(nullptr);
		Debug.logError("Buffer memory overflow!");
		Debug.logWarning("Buffer memory limit reached! Consider allocating more memory.");
		Debug.logMessage("Allocated {} bytes at {}", 1024, &Debug);
	}
};

Engine::App* Engine::createApp()
{
	return new Application();
}