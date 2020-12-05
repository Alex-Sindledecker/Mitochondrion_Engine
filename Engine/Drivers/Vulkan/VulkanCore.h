#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace vk
{

	bool init(GLFWwindow* windowPtr);
	void terminate();
	void _createInstance();
	bool _checkValidationLayerSupport();
	bool _checkInstanceExtensionSupport(const char** extensions, int count);
	void _createSurface();

}