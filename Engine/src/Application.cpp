#include "pch.h"

#include <glad/glad.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Window.h"
#include "Core/ThreadPool.h"
#include "Debug/Debug.h"
#include "Rendering/Renderer.h"

#include <iostream>

//TODO: Game loop. Add both fixed timesteps and non-fixed time steps

std::mutex m;

struct Color
{
	Engine::u8 r, g, b;
};

int main(int argc, char** argv)
{
	//Initialize core systems and create window
	Engine::Debug::init();
	Window::init(ENGINE_GL_WINDOW);
	Window window(1280, 720, "Testing...");
	Engine::PipelineInitStatus renderPipelineStatus = Engine::Renderer::initForGLPipeline(Window::getGLLoadProc);
	if (renderPipelineStatus.code != RENDER_PIPELINE_INIT_SUCCESS)
		Engine::Debug::logError(renderPipelineStatus.string);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	const char* v = "#version 410";
	ImGui_ImplGlfw_InitForOpenGL(window.getPtr(), true);
	ImGui_ImplOpenGL3_Init(v);

	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	Engine::Renderer::setClearColorRGB(0, 0, 0);
	while (!window.isCloseRequested())
	{
		for (const auto& event : window.pollEvents())
		{
			if (event.type == EventType::KEY_RELEASE && event.key.code == Key::ESCAPE)
				window.close();
		}

		Engine::Renderer::clearActiveFramebuffer();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);

		ImGui::Render();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		window.swapBuffers();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	//Terminate core systems
	Window::terminate();

	return 0;
}