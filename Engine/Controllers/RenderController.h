#pragma once

#include "Controllers/Window.h"
#include "Core/Model.h"
#include "Core/Loaders.h"
#include <glm/glm.hpp>

using MeshID = util::u32;

class RenderController
{
public:

	static RenderController& get();
	void init(Window& renderWindow);
	void terminate();
	MeshID addBGLSmesh(BGLSmeshBuffer& buffer);
	
	void render(MeshID mesh, unsigned int count);

	void operator=(const RenderController&) = delete;
	RenderController(const RenderController&) = delete;

private:
	RenderController() {}
	~RenderController() {}

	Viewport viewport;
	glm::mat4 projection, view;
	float near, far, fov, aspectRatio;


#ifdef USE_VULKAN

#else
	
#endif
};
