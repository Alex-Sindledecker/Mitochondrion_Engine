#include "mepch.h"
#include "Application.h"

#include "Drivers/OpenGL/GLCore.h"

Application::Application(Version version, const char* name)
{
	this->version = version;
	this->name = name;
}

Application::~Application()
{
}

void Application::init()
{
	window.reset(NEW Window(name));
	gl::init();
}

void Application::run()
{
	FrameLen timeStep = FrameLen(1);
	asyncTasks.enqueue(physicsLoop, this, timeStep * 2);
	gameLoop(this, timeStep);
}

void Application::terminate()
{

	gl::terminate();
	window->close();
}

void Application::gameLoop(Application* app, FrameLen timeStep)
{
	while (!app->window->shouldClose())
	{
		EventController::pollEvents();
		
		gl::clear();

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
