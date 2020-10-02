#pragma once

#include "Core.h"

namespace Engine
{

	class Renderer3D
	{
	public:
		static void init();

		Renderer3D(const Renderer3D&) = delete;
		void operator=(const Renderer3D&) = delete;

	private:
		Renderer3D() {}
		~Renderer3D() {}
	};

}