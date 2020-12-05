#include "mepch.h"
#include "Application.h"

#include "Core/Loaders.h"

RenderController& Application::renderer = RenderController::get();
AssetController& Application::assetManager = AssetController::get();

Application::Application(Version version, const char* name)
{
	this->version = version;
	this->name = name;
}

Application::~Application()
{
}

MeshID meshID;
void Application::init()
{
	window.reset(NEW Window(name));
	renderer.init(*window.get());
	assetManager.init();

	EngineDebugger::beginProfilingSession("Asset Loading");

	DBG_PROFILE2(auto meshBuffer, addBGLSmesh, "res/models/sponza.bgls");
	DBG_PROFILE2(meshID, renderer.addBGLSmesh, meshBuffer);

	EngineDebugger::ProfilingSession assetLoadingSession = EngineDebugger::endProfilingSession();

	EngineDebugger::printProfilingSession(assetLoadingSession);
}

void Application::run()
{
	FrameLen timeStep = FrameLen(1);
	asyncTasks.enqueue(physicsLoop, this, timeStep * 2);
	gameLoop(this, timeStep);
}

void Application::terminate()
{
	renderer.terminate();
	window->close();
}

void Application::gameLoop(Application* app, FrameLen timeStep)
{
	while (!app->window->shouldClose())
	{
		EventController::pollEvents();
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderer.render(meshID, 786615);

		app->window->update();

		auto now = std::chrono::high_resolution_clock::now();
		auto end = now + timeStep;
		std::this_thread::sleep_until(end);
	}
}

void Application::physicsLoop(Application* app, FrameLen timeStep)
{
	while (true)
	{


		auto now = std::chrono::high_resolution_clock::now();
		auto end = now + timeStep;
		std::this_thread::sleep_until(end);
	}
}
