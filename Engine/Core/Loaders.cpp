#include "mepch.h"
#include "Loaders.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stbimage.h>

BGLSmeshBuffer addBGLSmesh(const std::string& src)
{
	std::ifstream f(src, std::ios::binary);

	if (f.is_open())
	{
		BGLSmeshBuffer buffer;

		f.read((char*)&buffer.vertexBufferSize, 16);

		buffer.vertices = new Vertex[buffer.vertexBufferSize / sizeof(Vertex)];
		buffer.indices = new util::u32[buffer.indexBufferSize / sizeof(util::u32)];
		EngineDebugger::log(util::formatString("Loaded mesh with {} vertices and {} indices", buffer.vertexBufferSize / sizeof(Vertex), buffer.indexBufferSize / sizeof(util::u32)));

		f.read((char*)buffer.vertices, buffer.vertexBufferSize);
		f.read((char*)buffer.indices, buffer.indexBufferSize);
		f.close();

		return buffer;
	}
	else
	{
		EngineDebugger::log(util::formatString("Could not find BGLS mesh located at {}!", src), EngineDebugger::LogType::ERR);
		return { 0, 0, nullptr, nullptr };
	}
}

Image loadImage(const char* src)
{
	Image image;
	image.pixels = stbi_load(src, &image.width, &image.height, &image.channels, 0);
	return image;
}

void freeImage(Image* image)
{
	stbi_image_free(image->pixels);
}

void readFile(const std::string& src, std::string* dest)
{
	std::ifstream file(src);
	if (file.is_open())
	{
		std::stringstream ss;
		ss << file.rdbuf();
		*dest = ss.str();
	}
	else
	{
		*dest = "File not found!";
	}
}