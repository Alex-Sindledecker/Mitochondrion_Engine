#include "mepch.h"
#include "Application.h"

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
	window.reset(NEW Window("Hello World!"));
}

void Application::run()
{
	while (!window->shouldClose())
	{
		EventController::pollEvents();
	}
}

void Application::terminate()
{
	window->close();
}
