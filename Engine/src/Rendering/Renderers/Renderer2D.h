#pragma once

#include "Core.h"

namespace Engine
{

	class Renderer2D
	{
	public:
		static void init();

		Renderer2D(const Renderer2D&) = delete;
		void operator=(const Renderer2D&) = delete;

	private:
		Renderer2D() {}
		~Renderer2D() {}
	};

}
