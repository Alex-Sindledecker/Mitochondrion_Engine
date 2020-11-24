#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

struct Viewport
{
	int x, y, width, height;
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

private:
	void setWindowHints();

	GLFWwindow* window;
	int width, height;
};

