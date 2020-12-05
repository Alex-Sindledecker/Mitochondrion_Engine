#pragma once

#ifdef USE_VULKAN
#include "Drivers/Vulkan/VulkanCore.h"
#else
#include "Drivers/OpenGL/GLCore.h"
#endif
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

struct Viewport
{
	float x, y, width, height;
};

class Window
{
public:
	Window(uint32_t width, uint32_t height, const char* title);
	Window(const char* title);
	~Window();

	void close();
	void update();
	Viewport getViewport();
	glm::vec2 getSize();
	bool shouldClose();
	GLFWwindow* getGlfwWindowHandle();

private:
	void setWindowHints();

	GLFWwindow* window;
	int width, height;
};

