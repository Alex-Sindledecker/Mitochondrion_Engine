#pragma once

#include "Debug/EngineDebugger.h"
#include "Utilities.h"
#include <glm/glm.hpp>

struct Vertex
{
	glm::vec3 pos, normal;
	glm::vec2 uv;
};

struct BGLSmeshBuffer
{
	size_t vertexBufferSize;
	size_t indexBufferSize;
	Vertex* vertices;
	util::u32* indices;
};

struct Image
{
	int width, height, channels;
	unsigned char* pixels;
};

BGLSmeshBuffer addBGLSmesh(const std::string& src);
Image loadImage(const char* src);
void freeImage(Image* image);
void readFile(const std::string& src, std::string* dest);