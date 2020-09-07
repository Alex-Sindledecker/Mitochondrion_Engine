#include <stdio.h>
#include <Engine.h>
#include <Application/EntryPoint.h>
#include <chrono>
#include <thread>

class Application : public Engine::App
{
public:
	void run() override
	{
		while(true)
		{
			printf("Hello World!");
			using namespace std::chrono_literals;
			std::this_thread::sleep_for(1s);
		}
	}
};

Engine::App* Engine::createApp()
{
	return new Application();
}