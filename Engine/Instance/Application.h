#pragma once

#include "Core/Debug/EngineDebugger.h"
#include "Controllers/EventController.h"
#include "Controllers/Window.h"
#include "Core/Utilities.h"

#include <memory>

struct Version
{
	int major, minor, update;
};

class Application
{
	using FrameLen = std::chrono::duration<int, std::ratio<1, 60>>;
public:
	Application(Version version = { 0, 0, 0 }, const char* name = "Mitochondrion Engine");
	~Application();

	void init();
	void run();
	void terminate();

private:
	static void gameLoop(Application* app, FrameLen timeStep = FrameLen(0));
	static void physicsLoop(Application* app, FrameLen frameTime);

	Version version;
	const char* name;
	std::shared_ptr<Window> window;
	util::ThreadPool asyncTasks;
};

