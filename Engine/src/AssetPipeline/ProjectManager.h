#pragma once

#include "Core.h"

namespace Engine
{

	struct ProjectSettings
	{
		struct
		{
			u32_t width;
			u32_t height;
		} window;
	};
	
	struct Asset
	{
		guid_t id;
		guid_t pathId;
		std::vector<guid_t> dependencies;
	};

	struct Project
	{
		ProjectSettings settings;
		std::vector<Asset> assets;
		std::unordered_map<guid_t, std::string> assetNames;
		std::unordered_map<guid_t, std::string> filePaths;
		void save();
	};

	Project loadProject(const char* path);
	Project createProject(const char* dir);

}