#include "pch.h"
#include "ProjectManager.h"
#include "Core/FileManager.h"
#include "Debug/Debug.h"

#include <json11/json11.hpp>

namespace Engine
{

	static void loadSettings(json11::Json& json, ProjectSettings& settings)
	{
		settings.window.width = json["Properties"]["Window-Width"].int_value();
		settings.window.height = json["Properties"]["Window-Height"].int_value();
	}

	static void loadAssets(json11::Json& json, Project& project)
	{
		static std::hash<std::string> hashString;

		for (auto jAsset : json["Assets"].object_items())
		{
			Asset asset;

			json11::Json assetProperties = jAsset.second;
			for (auto dependency : assetProperties["Dependencies"].object_items())
			{
				guid_t dependencyID = hashString(dependency.second.string_value());
				asset.dependencies.push_back(dependencyID);
			}

			asset.pathId = hashString(jAsset.second["File-Path"].string_value());
			asset.id = hashString(jAsset.first);

			project.assetNames[asset.id] = jAsset.first;
			project.filePaths[asset.pathId] = jAsset.second["File-Path"].string_value();

			project.assets.push_back(asset);
		}
	}

	Project loadProject(const char* path)
	{
		Project project;
	
		std::string projectFileString;
		std::string jsonErrorString;

		loadFile(path, &projectFileString);
		json11::Json json = json11::Json::parse(projectFileString, jsonErrorString);

		loadSettings(json, project.settings);
		loadAssets(json, project);

		return project;
	}

	Project createProject(const char* dir)
	{
		Project project;

		return project;
	}

	void Project::save()
	{
	}

}