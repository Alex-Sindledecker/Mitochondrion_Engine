#pragma once

#include "Core/Utilities.h"
#include "Core/Model.h"

using AssetID = uint32_t;

constexpr AssetID SPRITE_MODEL = 0;

class AssetController
{
public:

	static AssetController& get();
	void init();
	void terminate();
	AssetID loadMesh(const char* filepath);
	AssetID loadTexture(const char* filepath);
	AssetID loadHDR(const char* filepath);
	AssetID unloadModel(AssetID id);
	AssetID unloadTexture(AssetID id);
	AssetID unloadHDR(AssetID id);

	AssetController(const AssetController&) = delete;
	void operator=(const AssetController&) = delete;

private:
	AssetController() {}
	~AssetController() {}

	
};