#pragma once

#include "Core/Debug/EngineDebugger.h"
#include "Controllers/EventController.h"
#include "Controllers/Window.h"

#include <memory>

struct Version
{
	int major, minor, update;
};

class Application
{
public:
	Application(Version version = { 0, 0, 0 }, const char* name = "Mitochondrion Engine");
	~Application();

	void init();
	void run();
	void terminate();

private:
	Version version;
	const char* name;
	std::shared_ptr<Window> window;
};

