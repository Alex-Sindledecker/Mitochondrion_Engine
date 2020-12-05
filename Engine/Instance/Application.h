#pragma once

#include "Core/Debug/EngineDebugger.h"
#include "Controllers/RenderController.h"
#include "Controllers/EventController.h"
#include "Core/Utilities.h"
#include "Core/Model.h"

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

	static RenderController& renderer;
	static AssetController& assetManager;

	Version version;
	const char* name;
	std::shared_ptr<Window> window;
	util::ThreadPool asyncTasks;
};

