#pragma once

#include "Renderer2D.h"
#include "Renderer3D.h"

namespace Engine
{

	class Renderer
	{
	public:
		static void init();

		Renderer(const Renderer&) = delete;
		void operator=(const Renderer&) = delete;

	private:
		Renderer() {}
		~Renderer() {}
	};

}