#include "pch.h"
#include "GUILayer.h"
#include "Debug/Debug.h"

#include "Rendering/Renderer.h"
static float screenColor[4] = { 0.109, 0.222, 0.386 };

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

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

		if (directoryHandleResult != "")
		{
			Debug::logMessage("Loading project {}", directoryHandleResult);
			directoryHandleResult = "";
		}
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
			static Directory currentDir = Directory("C:/");

			ImGui::Begin("Open File", &displayOpenFileDialoge);

			if (ImGui::ArrowButton("File Nav Back Button", ImGuiDir_Left))
				currentDir.assign(currentDir.path().parent_path());

			if (currentDir.is_directory())
				currentDir = openFileDialoge(currentDir);
			else if (currentDir.is_regular_file())
			{
				ImGui::Begin("Confirmation");
				ImGui::Text("Are you sure you want to open: \n%s?", currentDir.path().filename().string().c_str());
				if (ImGui::Button("Yes"))
				{
					directoryHandleResult = currentDir.path().string().c_str();
					currentDir.assign(currentDir.path().parent_path());
					displayOpenFileDialoge = false;
				}
				else if (ImGui::Button("No"))
					currentDir.assign(currentDir.path().parent_path());
				ImGui::End();
			}

			ImGui::End();
		}
	}

	GUILayer::Directory GUILayer::openFileDialoge(const Directory& searchDirectory)
	{
		for (const Directory& dir : DirectoryIterator(searchDirectory))
		{
			if (dir.is_directory() || dir.is_regular_file())
			{
				if (ImGui::Button(dir.path().filename().string().c_str()))
					return dir;
			}
		}
		return searchDirectory;
	}

}