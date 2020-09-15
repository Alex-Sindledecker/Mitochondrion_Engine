#include <Engine.h>
#include <Debug/Debug.h>
#include <Debug/Logging/FileLog.h>

#include <iostream>
#include <thread>
#include <Windows.h>

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