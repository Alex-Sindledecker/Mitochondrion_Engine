#include "pch.h"
#include "Application.h"
#include "Layers/GUILayer.h"
#include "Layers/TestingLayer.h"
#include "AssetPipeline/ProjectManager.h"

Engine::Project getProject(const char* path)
{
	if (path == "")
	{
		Engine::Project emptyProject;
		emptyProject.settings.window.width = 800;
		emptyProject.settings.window.height = 600;
		emptyProject.name = "Unsaved Project";
		return emptyProject;
	}
	else
		return std::move(Engine::loadProject(path));
}

int main(int argc, char* argv[])
{
	const char* projectPath = "";
	if (argc > 1)
		projectPath = argv[1];

	Engine::Project project = std::move(getProject(projectPath));

	Engine::Debug::init();
	Engine::Application::init(std::move(project));
	Engine::RenderPipelineInitStatus status = Engine::Renderer::init(Engine::Application::getWindow().getPtr());
	if (status.code != RENDER_PIPELINE_INIT_SUCCESS)
	{
		Engine::Debug::logError(status.string);
		return status.code;
	}

	//TODO: GUILayer really sucks right now. Needs complete refactoring
	//Engine::GUILayer layer;
	//Engine::Application::pushLayer("GUI Layer", &layer);

	Engine::TestingLayer testLayer;
	Engine::Application::pushLayer("Test Layer", &testLayer);

	Engine::Application::run();

	Engine::Renderer::terminate();
	Engine::Application::terminate();
	Engine::Debug::terminate();

	return 0;
}
