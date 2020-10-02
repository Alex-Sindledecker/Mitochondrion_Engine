#include "pch.h"
#include "Application.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace Engine
{

	Window Application::window;
	ThreadPool Application::asyncTaskManager;
	StackAllocator Application::singleFrameStack;
	std::mutex Application::physicsAccessMutex;

	void Application::init()
	{
		asyncTaskManager.start(7);
		window.create(1280, 720, "Engine");
	
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
	}

	void Application::terminate()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		asyncTaskManager.finish();
	}

	Window Application::getWindow()
	{
		return window;
	}

	void Application::run()
	{
		ImGui_ImplGlfw_InitForOpenGL(window.getPtr(), true);
		ImGui_ImplOpenGL3_Init("#version 410");

		loadDependencies();

		asyncTaskManager.enqueue(runPhysics);

		Engine::Renderer::setNormalizedClearColorRGB(screenColor[0], screenColor[1], screenColor[2]);
		while (!window.isCloseRequested())
		{
			singleFrameStack.clear();

			handleEvents();

			Engine::Renderer::clearActiveFramebuffer();
			beginFrame();
			endFrame();
			window.swapBuffers();
		}
	}

	void Application::setStaticTickRate(float ms)
	{
	}

	void Application::loadDependencies()
	{
	}

	void Application::beginFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		std::lock_guard<std::mutex> lk(physicsAccessMutex);
		processGame();
		processGui();
	}

	void Application::endFrame()
	{
		renderGame();
		renderGui();
	}

	void Application::handleEvents()
	{
		for (const auto& event : window.pollEvents())
		{
			if (event.type == Engine::EventType::KEY_RELEASE && event.key.code == Engine::Key::ESCAPE)
				window.close();
		}
	}

	void Application::processGame()
	{
	}

	void Application::renderGame()
	{
	}

	static float screenColor[4] = { 0.109, 0.222, 0.386 };
	void Application::processGui()
	{
		ImGui::Begin("Display Properties", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

		if (ImGui::ColorEdit3("Clear Color", screenColor))
		{
			Engine::Renderer::setNormalizedClearColorRGB(screenColor[0], screenColor[1], screenColor[2]);
		}
		static bool loadModelButtonWasPressed = false;
		if (ImGui::Button("Load Model") || loadModelButtonWasPressed)
		{
			loadModelButtonWasPressed = true;
			ImGui::Begin("File Select", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
			ImGui::Text("Hello");
			ImGui::Indent();
			ImGui::Text("World");
			ImGui::End();
		}

		ImGui::End();
	}

	void Application::renderGui()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void Application::runPhysics()
	{
	}

}