#include "pch.h"
#include "GUILayer.h"
#include "Debug/Debug.h"
#include "Application.h"
#include "Rendering/Renderer.h"

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
		//Booleans for displaying certain windows
		static bool displayPreferencesWindow = false;
		static bool displayOpenProjectDialoge = false;
		static bool displayNewProjectDialoge = false;
		static bool displaySaveProjectDialoge = false;

		//Main menu bar
		ImGui::BeginMainMenuBar();

		if (ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("New Project", "Ctrl-N", &displayNewProjectDialoge);
			ImGui::MenuItem("Open Project", "Ctrl-O", &displayOpenProjectDialoge);
			ImGui::MenuItem("Save Project", "Ctrl-S", &displaySaveProjectDialoge);
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

		//Preferences window
		if (displayPreferencesWindow)
		{
			ImGui::Begin("Preferences", &displayPreferencesWindow, ImGuiWindowFlags_AlwaysAutoResize);
			if (ImGui::ColorEdit3("Clear Color", screenColor))
			{
				Engine::Renderer::setNormalizedClearColorRGB(screenColor[0], screenColor[1], screenColor[2]);
			}
			ImGui::End();
		}
		
		//Open file dialoges
		if (displayOpenProjectDialoge)
		{
			displayNewProjectDialoge = false;
			displaySaveProjectDialoge = false;
			static Directory projectSearchRoot = Directory("C:\\");
			openFileDialoge("Open Project", &projectSearchRoot, &displayOpenProjectDialoge, ".json", [=](FileInfo info) {
				Debug::logMessage("Loading project {} at {}...", info.name, info.path);

				workingDirectory = info.path;
				Application::changeProject(std::move(loadProject( (info.path + info.name).c_str() )));
			});
		}
		else if (displayNewProjectDialoge)
		{
			displayOpenProjectDialoge = false;
			displaySaveProjectDialoge = false;
			static Directory projectSearchRoot = Directory("C:\\");
			selectDirectoryDialoge("New Project", &projectSearchRoot, &displayNewProjectDialoge, [=](FileInfo info) {
				Debug::logMessage("Creating new project at {}...", info.path);

				workingDirectory = info.path;
				saveProject(Application::getProject(), workingDirectory);
			});
		}
		else if (displaySaveProjectDialoge)
		{
			Project& project = Application::getProject();
			if (project.name == "Unsaved Project")
			{
				displayOpenProjectDialoge = true;
				displaySaveProjectDialoge = false;
			}
			else
				saveProject(project, workingDirectory);
		}
	}

	void GUILayer::openFileDialoge(const char* title, Directory* startDirectory, bool* isOpen, const char* extensionContraints, FileCallback callback)
	{
		static bool displayFileConfirm = false;

		ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(1980, 720));
		ImGui::Begin(title, isOpen, ImGuiWindowFlags_AlwaysAutoResize);

		if (ImGui::ArrowButton("File Nav Back Button", ImGuiDir_Left))
			startDirectory->assign(startDirectory->path().parent_path());
		ImGui::SameLine();
		ImGui::Text("Current Directory"); ImGui::SameLine();
		static char inputDirectoryBuffer[256];
		strncpy_s(inputDirectoryBuffer, startDirectory->path().string().c_str(), startDirectory->path().string().size());
		if (ImGui::InputText("", inputDirectoryBuffer, 256))
			startDirectory->assign(Directory(inputDirectoryBuffer));

		ImGui::NewLine();

		static Directory selectedDir("");
		try
		{
			for (const Directory& dir : DirectoryIterator(*startDirectory))
			{
				if (dir.is_directory())
				{
					if (ImGui::Button(dir.path().filename().string().c_str()))
						startDirectory->assign(dir);
				}
				else if (dir.is_regular_file())
				{
					if (extensionContraints != "" && dir.path().extension() == extensionContraints)
					{
						if (ImGui::Button(dir.path().filename().string().c_str()))
						{
							selectedDir = dir;
							displayFileConfirm = true;
						}
					}
				}
			}
		}
		catch (std::filesystem::filesystem_error e)
		{
			Debug::logWarning("File system error when trying to access {}!", startDirectory->path().string());
		}

		confirmMenu("Confirm?", selectedDir.path().string(), &displayFileConfirm, [=] {
			*isOpen = false;

			Engine::GUILayer::FileInfo info(selectedDir.path().parent_path().string(),
											selectedDir.path().filename().string(),
											selectedDir.path().filename().extension().string());
			callback(info);
		});

		ImGui::End();
	}

	void GUILayer::selectDirectoryDialoge(const char* title, Directory* startDirectory, bool* isOpen, FileCallback callback)
	{
		static bool displayConfirmation = false;

		ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(1980, 720));
		ImGui::Begin(title, isOpen, ImGuiWindowFlags_AlwaysAutoResize);

		if (ImGui::ArrowButton("File Nav Back Button", ImGuiDir_Left))
			startDirectory->assign(startDirectory->path().parent_path());
		ImGui::SameLine();
		ImGui::Text("Current Directory"); ImGui::SameLine();
		static char inputDirectoryBuffer[256];
		strncpy_s(inputDirectoryBuffer, startDirectory->path().string().c_str(), startDirectory->path().string().size());
		if (ImGui::InputText("", inputDirectoryBuffer, 256))
			startDirectory->assign(Directory(inputDirectoryBuffer));
		ImGui::SameLine();
		if (ImGui::Button("Use This Directory"))
			displayConfirmation = true;

		ImGui::NewLine();

		if (startDirectory->is_directory())
		{
			try
			{
				for (const Directory& dir : DirectoryIterator(*startDirectory))
				{
					if (dir.is_directory())
					{
						if (ImGui::Button(dir.path().filename().string().c_str()))
							startDirectory->assign(dir);					
					}
				}
			}
			catch (std::filesystem::filesystem_error e)
			{
				Debug::logWarning("File system error when trying to access {}! Reverting to previous directory...", startDirectory->path().string());
				startDirectory->assign(startDirectory->path().parent_path());
			}
		}

		if (displayConfirmation)
		{
			confirmMenu("Confirm Directory?", startDirectory->path().string(), &displayConfirmation, [=] {
				*isOpen = false;

				Engine::GUILayer::FileInfo info(startDirectory->path().string(),
					startDirectory->path().filename().string(),
					"");
				callback(info);
			});
		}

		ImGui::End();
	}

	void GUILayer::confirmMenu(const char* title, const std::string& message, bool* isOpen, VoidCallback callback)
	{
		if (*isOpen)
		{
			ImGui::Begin(title, nullptr, ImGuiWindowFlags_AlwaysAutoResize);

			ImGui::Text("Confirm: %s?", message.c_str());
			if (ImGui::Button("Yes"))
			{
				callback();
				*isOpen = false;
			}
			ImGui::SameLine();
			if (ImGui::Button("No"))
				*isOpen = false;

			ImGui::End();
		}
	}

}