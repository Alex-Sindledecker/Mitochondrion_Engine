#include "pch.h"
#include "GUILayer.h"
#include "Debug/Debug.h"

#include "Rendering/Renderer.h"
static float screenColor[4] = { 0.109, 0.222, 0.386 };

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <filesystem>

namespace Engine
{

	void GUILayer::onLoad()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(window->getPtr(), true);
		ImGui_ImplOpenGL3_Init("#version 410");

		Engine::Renderer::setNormalizedClearColorRGB(screenColor[0], screenColor[1], screenColor[2]);
	}

	void GUILayer::onFrameStart()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		buildGUI();
	}

	void GUILayer::onFrameEnd()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void GUILayer::onClose()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void GUILayer::buildGUI()
	{
		static bool displayPreferencesWindow = false;
		static bool displayOpenFileDialoge = false;

		ImGui::BeginMainMenuBar();

		if (ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("Open Project", "Ctrl-o", &displayOpenFileDialoge);
			if (ImGui::MenuItem("Quit"))
				window->close();
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit"))
		{
			ImGui::MenuItem("Preferences", 0, &displayPreferencesWindow);
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();

		if (displayPreferencesWindow)
		{
			ImGui::Begin("Preferences", &displayPreferencesWindow, ImGuiWindowFlags_AlwaysAutoResize);
			if (ImGui::ColorEdit3("Clear Color", screenColor))
			{
				Engine::Renderer::setNormalizedClearColorRGB(screenColor[0], screenColor[1], screenColor[2]);
			}
			ImGui::End();
		}

		if (displayOpenFileDialoge)
		{
			static std::string searchDirectory = "C:/";
			static std::string lastSearchDirectory = "C:/";

			ImGui::Begin("Open Project", &displayOpenFileDialoge);

			if (ImGui::ArrowButton("Back", ImGuiDir_Left))
				searchDirectory.swap(lastSearchDirectory);
			if (ImGui::ArrowButton("Back", ImGuiDir_Right))
				lastSearchDirectory.swap(searchDirectory);

			for (const std::filesystem::directory_entry& dir : std::filesystem::directory_iterator(searchDirectory))
			{
				if (dir.is_directory() || dir.is_regular_file())
				{
					if (ImGui::Button(dir.path().filename().string().c_str()))
					{
						if (dir.is_directory())
						{
							lastSearchDirectory = searchDirectory;
							searchDirectory = dir.path().string();
						}
					}
				}
			}

			ImGui::End();
		}
	}

}