#pragma once

///
/// Mitochondrion Engine - Not copyrighted 2020
/// Alex Sindledecker
/// 
/// TODO: enter a description here
/// 

//Platform specific includes
#ifdef MITO_USE_VULKAN_API
//Vulkan includes
#else
#include "mito-platform/OpenGL/GLCore.h"
#endif

//Standard engine includes
#include "mito/Core/MitochondriaAPI.h"
#include "mito/Debug/Debug.h"
#include "mito/Core/Application.h"
#include "mito/Core/Event.h"