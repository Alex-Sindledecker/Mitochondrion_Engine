#pragma once

#include "Layer.h"

#include <filesystem>

namespace Engine
{

	class GUILayer : public Layer
	{
	private:
		using Directory = std::filesystem::directory_entry;
		using DirectoryIterator = std::filesystem::directory_iterator;
	public:
		virtual void onLoad() override;
		virtual void onFrameStart() override;
		virtual void onFrameEnd() override;
		virtual void onClose() override;

	private:
		void buildGUI();
		Directory openFileDialoge(const Directory& searchDirectory);

		std::string directoryHandleResult = "";
	};

}