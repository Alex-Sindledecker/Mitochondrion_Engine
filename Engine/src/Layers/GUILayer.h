#pragma once

#include "Layer.h"

#include <filesystem>
#include <functional>

namespace Engine
{

	class GUILayer : public Layer
	{
	private:
		struct FileInfo
		{
			std::string path;
			std::string name;
			std::string extension;
			FileInfo(const std::string& path, const std::string& name, const std::string& extension)
				: path(path), name(name), extension(extension) {}
		};

		using Directory = std::filesystem::directory_entry;
		using DirectoryIterator = std::filesystem::directory_iterator;
		using FileCallback = std::function<void(FileInfo)>;
		using VoidCallback = std::function<void()>;

	public:
		virtual void onLoad() override;
		virtual void onFrameStart() override;
		virtual void onFrameEnd() override;
		virtual void onClose() override;

	private:
		void buildGUI();
		void openFileDialoge(const char* title, Directory* startDirectory, bool* isOpen, FileCallback callback); // add extension constraintes to parameters
		void selectDirectoryDialoge(const char* title, Directory* startDirectory, bool* isOpen, FileCallback callback);
		void confirmMenu(const char* title, const std::string& message, bool* isOpen, VoidCallback callback);

		float screenColor[4] = { 0.109, 0.222, 0.386 };
	};

}