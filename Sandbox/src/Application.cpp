#include <Engine.h>
#include <Renderer.h>

#include <iostream>

//TODO: Game loop. Add both fixed timesteps and non-fixed time steps

int main(int argc, char** argv)
{
	//Initialize core systems and create window
	Engine::Debug::init();
	Engine::Window::init(ENGINE_GL_WINDOW);
	Engine::Window window(1280, 720, "Testing...");
	Engine::PipelineInitStatus renderPipelineStatus = Engine::Renderer::initForGLPipeline(Engine::Window::getGLLoadProc);
	if (renderPipelineStatus.code == RENDER_PIPELINE_INIT_FAILURE)
		Engine::Debug::logError(renderPipelineStatus.string);

	while (!window.isCloseRequested())
	{
		for (const auto& event : window.pollEvents())
		{

		}

		window.swapBuffers();
	}


	//Terminate core systems
	Engine::Window::terminate();

	return 0;
}