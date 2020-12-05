#include "mepch.h"
#include "AssetController.h"

#include "Drivers/OpenGL/GLCore.h"

AssetController& AssetController::get()
{
    static AssetController instance;
    return instance;
}

void AssetController::init()
{
    
}

void AssetController::terminate()
{
}

AssetID AssetController::loadMesh(const char* filepath)
{
    return 0;
}

AssetID AssetController::loadTexture(const char* filepath)
{
    return 0;
}

AssetID AssetController::loadHDR(const char* filepath)
{
    return 0;
}

AssetID AssetController::unloadModel(AssetID id)
{
    return 0;
}

AssetID AssetController::unloadTexture(AssetID id)
{
    return 0;
}

AssetID AssetController::unloadHDR(AssetID id)
{
    return 0;
}