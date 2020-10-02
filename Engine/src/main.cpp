#include "pch.h"
#include "Application.h"

int main(int argc, char** argv)
{
	Engine::Debug::init();
	Engine::Application::init();
	Engine::PipelineInitStatus status = Engine::Renderer::init(Engine::Application::getWindow().getGLLoadProc);
	if (status.code != RENDER_PIPELINE_INIT_SUCCESS)
	{
		Engine::Debug::logError(status.string);
		return status.code;
	}
	
	Engine::Application::run();

	Engine::Renderer::terminate();
	Engine::Application::terminate();
	Engine::Debug::terminate();
}
