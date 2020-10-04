#include "pch.h"
#include "Application.h"
#include "Layers/GUILayer.h"

int main(int argc, char* argv[])
{
	const char* projectDir = "";
	if (argc > 1)
		projectDir = argv[1];

	Engine::Debug::init();
	Engine::Application::init();
	Engine::PipelineInitStatus status = Engine::Renderer::init(Engine::Application::getWindow().getGLLoadProc);
	if (status.code != RENDER_PIPELINE_INIT_SUCCESS)
	{
		Engine::Debug::logError(status.string);
		return status.code;
	}

	Engine::GUILayer layer;
	Engine::Application::pushLayer("GUI Layer", &layer);

	Engine::Application::run();

	Engine::Renderer::terminate();
	Engine::Application::terminate();
	Engine::Debug::terminate();
}
